use university ;

SELECT * from student
where name = 'Shahed' OR Department = 'SWE';    # Use of OR

SELECT ID from student
where Department = 'CSE' AND Name = 'Munna' ;

SELECT ID,Name from student
where Department <> 'EEE';          # Use of NOT ....<> it also means 'NOT'

SELECT ID,Name from student
where not Department = 'SWE' ;      # Use of NOT