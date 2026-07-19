# Standard Database APIs

`std/sqlite` and `std/postgres` intentionally share a similar Result-first API:
open/close connections, prepare reusable statements, execute mutations, stream
queries, fetch one row, convert rows for JSON decoding, and control basic
transactions. Both use native client libraries and return categorized error
objects rather than panicking for database errors.

## `std/sqlite`

```doof
import {
  open, close, prepare, execute, executeSql, query, queryOne,
  begin, commit, rollback, toJsonRow,
  Database, Statement, ExecResult, SqliteError, SqliteParam, SqliteValue,
} from "std/sqlite"
```

- `open(":memory:")` creates an in-memory database.
- Parameters use `?` placeholders and accept `int | long | bool | double |
  string | readonly byte[] | null`.
- Rows are `Map<string, SqliteValue>` where SQLite integers are `long` and
  blobs are `readonly byte[]`.
- `query` returns `Stream<Result<Map<string, SqliteValue>, SqliteError>>`, so
  row conversion can fail during iteration.
- `execute` rejects a statement that unexpectedly produces rows.
- `ExecResult` contains `changes` and `lastInsertRowId`.
- `toJsonRow` maps blob values to `null`; boolean columns normally need an
  application schema or SQLite convention.

## `std/postgres`

```doof
import {
  open, close, prepare, execute, executeSql, query, queryOne,
  begin, commit, rollback, toJsonRow,
  Database, Statement, ExecResult, PostgresError, PostgresParam, PostgresValue,
} from "std/postgres"
```

- `open(connectionString)` accepts libpq strings and PostgreSQL URLs. The host
  needs libpq development headers and libraries.
- Prepared parameters use `$1`, `$2`, ... and accept the same value union as
  SQLite.
- Rows map PostgreSQL booleans to `bool`, integers to `long`, numeric/floating
  values to `double` when parseable, `BYTEA` to bytes, and other types to
  `string`.
- `query` streams `Result<Map<string, PostgresValue>, PostgresError>` rows;
  `queryOne` returns the first row or `null`.
- `ExecResult` contains `rowCount` and the PostgreSQL `commandTag`.
- `PostgresError.code` contains SQLSTATE when available; detail and SQL text are
  retained separately.

Prepared statements are connection-bound. Keep the connection and statement
alive until a returned row stream is fully consumed, and explicitly close
connections when their work is complete.
