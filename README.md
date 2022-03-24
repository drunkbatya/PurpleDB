# PurpleDB
Database mock for three unique tables: interactive interface, semi-competitive with SQL-like DBs - all you ever wanted.

```sql
PurpleDB :-( select * from modules where mem_level_modules = 4;
SELECT
	*
FROM
	modules
WHERE
	mem_level_modules = 4
 ---------------------------------------------------------------------------
| id     | module_name       | mem_level_modules | cell_num | deletion_flag |
|---------------------------------------------------------------------------|
| 0      | Main module       | 4                 | 3        | 0             |
| 4      | Some module 4     | 4                 | 3        | 0             |
| 8      | Some module 8     | 4                 | 4        | 0             |
| 11     | Some module 11    | 4                 | 1        | 0             |
| 20     | Some module 20    | 4                 | 1        | 0             |
| 22     | Some module 22    | 4                 | 2        | 0             |
| 26     | Some module 26    | 4                 | 1        | 0             |
| 28     | Some module 28    | 4                 | 4        | 0             |
| 42     | Some module 42    | 4                 | 1        | 0             |
| 43     | Some module 43    | 4                 | 3        | 0             |
| 44     | Some module 44    | 4                 | 4        | 0             |
| 54     | Some module 54    | 4                 | 1        | 0             |
| 55     | Some module 55    | 4                 | 4        | 0             |
| 57     | Some module 57    | 4                 | 4        | 0             |
| 67     | Some module 67    | 4                 | 3        | 0             |
| 85     | Some module 85    | 4                 | 4        | 0             |
| 88     | Some module 88    | 4                 | 4        | 0             |
| 91     | Some module 91    | 4                 | 1        | 0             |
| 95     | Some module 95    | 4                 | 4        | 0             |
| 98     | Some module 98    | 4                 | 2        | 0             |
 ---------------------------------------------------------------------------
