USE university ;

# Select
Select * from department ;    # It will show whole Table
SELECT * from student ;

Select name from student ;      # It will show only one Column

# Update
Update department
set Budget = 500000  ;      # It will update all the value of 'Budget'

Update department
set Budget = 250000
where `Number of teachers` <= 20   ;   # Now it will Update condition wise

# Using Case
UPDATE department
set Budget =
    CASE
        WHEN Name = 'CSE' then 500000
        WHEN Name = 'EEE' OR Name = 'SWE' then 300000      # Using OR
        else 200000                                        # If we use 'else' and not given anything after that it will be shown syntex error
END ;

# If we don't use 'else' after finding all the conditions false then it will go to default 'Null'
UPDATE department
set Budget =
    CASE
        WHEN Name = 'CSE' then 500000
        WHEN Name = 'EEE' OR Name = 'SWE' then 300000
END ;
UPDATE department
set Budget =
    CASE
        WHEN Name = 'CSE' then 500000
        WHEN Name = 'EEE' OR Name = 'SWE' then 300000
        else 200000
END
WHERE `Number of teachers` > 20 ;