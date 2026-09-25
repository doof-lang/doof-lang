fetch("api/v1/snapshot").then(response => response.json()).then(snapshot => {
  document.querySelector("p").textContent = `${snapshot.metrics.length} metric series`;
});
