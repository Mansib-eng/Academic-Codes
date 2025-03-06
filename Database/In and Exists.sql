use university2 ;

# Find the ID of the teachers that have taken courses both in Fall 2017 and Spring 2018
SELECT distinct ID as `both Fall 2017 and Spring 2018`
from teaches
where semester = 'Fall' and year = 2017 and ID in           # using 'IN'
(
    SELECT ID
    from teaches
    where semester = 'spring' and year = 2018
) ;

# Find the ID of the teachers that have taken courses in Fall 2017 but not in Spring 2018
SELECT distinct ID as `Fall 2017 but not Spring 2018`
from teaches
where semester = 'Fall' and year = 2017 and ID not in           # using 'not IN'
(
    SELECT ID
    from teaches
    where semester = 'spring' and year = 2018
) ;

# Find out the teachers that have taken at least one course in the Music department
SELECT name as `MUSIC TEACHER` from instructor
WHERE ID =(
SELECT ID from teaches
where exists(                                       # Using 'EXISTS'
    SELECT course_id
    from course
    where teaches.course_id = course.course_id
    AND dept_name = 'Music'
)) ;