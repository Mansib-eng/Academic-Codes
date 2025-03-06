use university ;

SELECT Name as Ascending_Name
from student
order by Name ;                       # It will show 'Name' in Ascending order


SELECT Name as Descending_Name
from student
order by Name desc ;                  # It will shoe 'Name' in Descending order

SELECT distinct name                  # By using 'Distinct' it will show distinct values
from airline