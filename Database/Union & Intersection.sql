use university ;

SELECT `Number of teachers` from department
where Name = 'CSE' and Budget = 500000
UNION                                         # Using UNION
(
SELECT `Number of teachers` from department
where Name = 'SWE' and Budget = 300000
) ;

SELECT Department from student
Where name = 'Shahed' and ID = 2020221050
INTERSECT                                    # Using INTERSECT
(
    SELECT Department from student
Where name = 'Monika' and ID = 2020331012
) ;

# There also a Query named 'Except' and 'Except All'
# This query generally use when two tables has same column and data types then by using 'Except' we can find out what the value has in the 1st table that is not in the 2nd table
# By using 'Except ALL' can also read duplicate values

/**
  Select 'Column Name'
  from Table 1
  Except
  Select 'Column Name'
  from Table 2
 */

/**
  Select 'Column Name'
  from Table 1
  Except All
  Select 'Column Name'
  from Table 2
 */
