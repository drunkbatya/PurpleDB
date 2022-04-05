# PurpleDB
SQL-compatible RAM-free micro database with pretty terminal output.

This is a school project written in Pure C in 2 days by [@Koterin](https://github.com/Koterin), [@drunkbatya](https://github.com/drunkbatya/) and [@GrusnyDance](https://github.com/GrusnyDance).

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
```
## List of avaliable commands
- show tables;
- describe table [table];
- select [column] from [table];
- select [column] from [table] where [column] = [value];
- insert into [table] values ([value1], [value2], ..);
- update [table] set [column] = [value] where [column] = [value];
- delete from [table] where [column] = [value];

```sql
--Warning! Spaces in strings are not supported, use backslash '\' to imitate them.
--Example:
select id from modules where module_name = Some\module\11;
```

## How to build
Just cd to src/ and type 'make' :
```bash
[~/dev/PurpleDB]: $ cd src/
[~/dev/PurpleDB/src]: $ make
```
Then simply run executable file
```bash
[~/dev/PurpleDB/src]: $ ../build/purpledb 
Welcome to PurpleDB!

PurpleDB :-( 
```

## How to use
### List of tables
This DBMS is not designed to create tables, instead it modifies 3 pre-defined data structures (stored in '.db' files that are located into materials/ folder).
To see the list of tables, type 'show databases;' :
```sql
PurpleDB :-( show tables;
SHOW TABLES

 -----name------
| modules       |
| levels        |
| status_events |
 ---------------
 ```

### Table structure
Standard SQL query 'describe table [table];' works here!
```sql
PurpleDB :-( describe table status_events;
DESCRIBE TABLE status_events

 ---------name-----------type---
| event_id           | int      |
| module_id          | int      |
| new_status         | int      |
| status_change_date | char[12] |
| status_change_time | char[9]  |
 -------------------------------
 ```
 
 ### Insert data
 You can insert INT or STRING values to corresponding columns
 ```sql
 PurpleDB :-( insert into modules values (167, I\Wanna\Test\It, 3, 2, 0);
INSERT INTO
	modules
VALUES
	167,
	I Wanna Test It,
	3,
	2,
	0
```

### Update data
Update works too:
```sql
PurpleDB :-( update modules set module_name = Empty\name where id = 98;
UPDATE 
	modules
SET
	module_name = Empty name
WHERE
	id = 98
```

Let's check:
```sql
PurpleDB :-( select module_name from modules where id = 98;
SELECT
	module_name
FROM
	modules
WHERE
	id = 98
 -------------------
| module_name       |
|-------------------|
| Empty name        |
 -------------------
 ```
 Enjoy...
