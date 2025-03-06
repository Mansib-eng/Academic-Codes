use university ;

select Department,count(name) as `No of Student`     # Using 'Count'
from student
group by Department ;                       # Using 'Group by'

SELECT count(DISTINCT Name) as `Name of Airlines`
from airline ;

SELECT count(*) as `Name of Airlines`     # by using (*) it will pick all not distinct
from airline
group by airline.name ;

SELECT Name as `Highest Budget Department`
from department
where Budget =
      (
          select max(Budget) as `MAX`       # using 'MAX'
          from department
          ) ;

SELECT Name as `Lowest Budget Department`
from department
where Budget =
      (
          select min(Budget) as `MIN`       # using 'MIN'
          from department
          ) ;


select avg(Budget) as `AVERAGE`             #using 'Avg'
from department
group by department.Name ;

select sum(Budget) as `SUM`       # Using 'Sum'
from department ;

select Name
from department
group by Name
having sum(Budget) > 200000                    # Using 'Having'
order by `Number of teachers` ;

select Name
from department
group by Name
having sum(Budget) > 200000                    # Using 'Having'
order by `Number of teachers` desc ;


/**
  Sequence should be followed =>
  Select...
  From...
  where...
  Group by...
  Having...
  Order by...
  */

    # There are more in 'Exercise' check it for more information