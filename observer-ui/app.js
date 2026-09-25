const metrics = new Map();
const previousMetrics = new Map();
let retainedLogs = [];
const seenLogIds = new Set();
const maximumLogs = 500;
const severity = { debug: 0, info: 1, warn: 2, error: 3, fatal: 4 };
let panicSeen = false;

const metricsElement = document.querySelector("#metrics");
const objectsElement = document.querySelector("#objects");
const metricCount = document.querySelector("#metric-count");
const logsElement = document.querySelector("#logs");
const connection = document.querySelector("#connection");
const logFilter = document.querySelector("#log-filter");
const logLevel = document.querySelector("#log-level");

function cell(text, parent) {
  const element = document.createElement("span");
  element.textContent = String(text);
  parent.append(element);
}

function renderMetrics() {
  metricsElement.replaceChildren();
  objectsElement.replaceChildren();
  metricCount.textContent = `${metrics.size} series`;
  if (metrics.size === 0) {
    metricsElement.className = "metrics empty";
    metricsElement.textContent = "No metrics recorded yet.";
    return;
  }
  metricsElement.className = "metrics";
  const classes = new Map();
  for (const [name, value] of [...metrics].sort(([left], [right]) => left.localeCompare(right))) {
    const row = document.createElement("div");
    row.className = "metric";
    cell(name, row);
    const previous = previousMetrics.get(name);
    const delta = previous === undefined ? "" : `  (${value - previous >= 0 ? "+" : ""}${value - previous})`;
    cell(`${value}${delta}`, row);
    metricsElement.append(row);

    const match = /^doof_class_(created|disposed)_total\{module="((?:\\.|[^"])*)",class="((?:\\.|[^"])*)"\}$/.exec(name);
    if (match) {
      const key = `${match[2]} · ${match[3]}`;
      classes.set(key, (classes.get(key) || 0) + (match[1] === "created" ? value : -value));
    }
  }
  for (const [name, count] of [...classes].sort(([left], [right]) => left.localeCompare(right))) {
    const row = document.createElement("div");
    row.className = "object-row";
    cell(`${name} live`, row);
    cell(count, row);
    objectsElement.append(row);
  }
  previousMetrics.clear();
  for (const [name, value] of metrics) previousMetrics.set(name, value);
}

function renderLogs() {
  logsElement.replaceChildren();
  const query = logFilter.value.trim().toLowerCase();
  const minimum = severity[logLevel.value] ?? 0;
  const visible = retainedLogs.map(item => item.entry).filter(entry => {
    if ((severity[entry.level] ?? 0) < minimum) return false;
    if (!query) return true;
    return `${entry.message || ""} ${entry.source?.file || ""} ${JSON.stringify(entry.context || {})}`
      .toLowerCase().includes(query);
  });
  if (visible.length === 0) {
    logsElement.className = "logs empty";
    const empty = document.createElement("li");
    empty.textContent = retainedLogs.length === 0 ? "Waiting for diagnostics." : "No matching logs.";
    logsElement.append(empty);
    return;
  }
  logsElement.className = "logs";
  for (const entry of visible.slice(-maximumLogs).reverse()) {
    const item = document.createElement("li");
    const level = document.createElement("span");
    level.className = `level level-${entry.level || "unknown"}`;
    level.textContent = entry.level || "unknown";
    const content = document.createElement("div");
    content.className = "log-content";
    const message = document.createElement("div");
    message.className = "log-message";
    message.textContent = entry.message || "";
    const meta = document.createElement("div");
    meta.className = "log-meta";
    const source = entry.source ? `${entry.source.file}:${entry.source.line}` : "unknown source";
    const context = entry.context && Object.keys(entry.context).length ? ` · ${JSON.stringify(entry.context)}` : "";
    meta.textContent = `${entry.timestamp || ""} · ${source}${context}`;
    content.append(message, meta);
    item.append(level, content);
    logsElement.append(item);
  }
}

function appendLog(entry, id) {
  if (id && seenLogIds.has(id)) return;
  if (id) seenLogIds.add(id);
  retainedLogs.push({ id, entry });
  if (retainedLogs.length > maximumLogs) retainedLogs = retainedLogs.slice(-maximumLogs);
  if (seenLogIds.size > maximumLogs * 2) {
    seenLogIds.clear();
    for (const item of retainedLogs) if (item.id) seenLogIds.add(item.id);
  }
  renderLogs();
}

async function refreshSnapshot() {
  const response = await fetch("api/v1/snapshot", { cache: "no-store" });
  if (!response.ok) throw new Error(`snapshot ${response.status}`);
  const snapshot = await response.json();
  metrics.clear();
  for (const metric of snapshot.metrics || []) metrics.set(metric.name, metric.value);
  const newer = retainedLogs.filter(item => item.id > snapshot.lastEventId);
  retainedLogs = [...(snapshot.logs || []), ...newer].slice(-maximumLogs);
  seenLogIds.clear();
  for (const item of retainedLogs) if (item.id) seenLogIds.add(item.id);
  renderMetrics();
  renderLogs();
  return snapshot.lastEventId || 0;
}

function connect(afterId) {
  const events = new EventSource(`api/v1/events?after=${afterId}`);
  events.onopen = () => {
    connection.dataset.state = "open";
    connection.textContent = "Live";
  };
  events.onerror = () => {
    connection.dataset.state = "closed";
    connection.textContent = "Reconnecting";
  };
  events.addEventListener("hello", event => {
    const hello = JSON.parse(event.data);
    connection.title = `Session ${hello.session} · API v${hello.version}`;
  });
  events.addEventListener("metrics", event => {
    for (const metric of JSON.parse(event.data).metrics || []) metrics.set(metric.name, metric.value);
    renderMetrics();
  });
  events.addEventListener("log", event => appendLog(JSON.parse(event.data), Number(event.lastEventId)));
  events.addEventListener("panic", event => {
    const diagnostic = JSON.parse(event.data);
    panicSeen = true;
    appendLog({ level: "fatal", message: `panic: ${diagnostic.message}`, context: {} }, Number(event.lastEventId));
    connection.dataset.state = "closed";
    connection.textContent = "Program panicked";
  });
  events.addEventListener("gap", () => refreshSnapshot().catch(() => {}));
  events.addEventListener("shutdown", () => {
    connection.dataset.state = "closed";
    if (!panicSeen) connection.textContent = "Program exited";
    events.close();
  });
}

document.querySelector("#clear-logs").addEventListener("click", () => {
  retainedLogs = [];
  renderLogs();
});
logFilter.addEventListener("input", renderLogs);
logLevel.addEventListener("change", renderLogs);

refreshSnapshot().then(connect).catch(() => connect(0));
