use university2 ;

/*
 'Join Operation' is very important if there is a relation between two tables.
 'Join Operation' can return a result relation
  There are three types 'Join Operation' =>   1. Natural Join
                                              2. Inner Join
                                              3. Outer Join
 'Join Operation' = Cross Product + Some Condition
 in 'Join operation' , if the total number of column in both table is not same then the table has most column will select and attach with other columns from table 2
 */

# using Default 'Join'
SELECT *
from student join takes ;

Select *
from student,takes ;
# Both return same

select dept_name,room_number,capacity
from department join classroom on department.building = classroom.building ;

select *
from department join classroom on department.building = classroom.building ;

# Using 'Natural Join' which need a condition where name of the column of two tables are same
SELECT *
from student join takes ON student.ID = takes.ID ;   # Condition must be there

SELECT *
from student join takes
where student.ID = takes.ID ;
# These two are same

SELECT *
from student natural join takes
where student.ID = takes.ID ;
/*
There is slightly different in 'Join' and 'Natural Join'...
In Join, Same name Column will be presented as different table name.column
In 'Natural Join', Same name Column will be presented just once

If the column name are changed then both column will come otherwise just one column will come to the natural join relation
If datatype different then there will be no error but there will show no relation table
 */

# Using 'Inner Join'
# It's most like default 'join'
SELECT name,building
from student inner join department ON student.dept_name = department.dept_name ;

SELECT *
from student inner join department ON student.dept_name = department.dept_name ;

SELECT *
from student inner join takes ON student.ID = takes.ID ;

SELECT name,building
from student inner join department  ;

select *
from student NATURAL inner join department ;     # It not good to use all time

# Outer Join in 'Outer_Join.sql' file

# Write a Query that shows the name of student and their advisor name
SELECT student.name,instructor.name
from (student join advisor on student.ID = advisor.s_ID)           # Natural join kaj krbe na -> student r instructor r nam same na
join instructor on instructor.ID = advisor.i_ID;

SELECT instructor.name,student.name
    from (advisor join instructor
on advisor.i_ID = instructor.ID) join student on advisor.s_ID = student.ID ;
# Both are same