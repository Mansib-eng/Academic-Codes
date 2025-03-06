]/*
 Alter is used to
 1. Add a new column
 2. Delete a column
 3. Edit a column
 */

# Add a Column
 use university ;
ALTER TABLE student
ADD COLUMN CGPA DECIMAL(3,2) check ( CGPA>0 ) ;    # Using Check

UPDATE student
set CGPA =
CASE
        when name = 'Shahed' then 3.40
        when name = 'Unayes' then 3.80
        when name = 'munna' then 3.00
        when name = 'mansib' then 3.75
        when name = 'Monika' then 3.50
else 3.25
END ;

# Edit a Column
ALTER TABLE student
MODIFY COLUMN CGPA DECIMAL(4,3) ;         # Change column type

Alter TABLE student
CHANGE COLUMN CGPA GPA DECIMAL(4,3) ;      # Change column name
    /*
     If the above not work then use this =>
     Rename Column CGPA to GPA ;
     */

# Drop a column
ALTER TABLE student
DROP COLUMN GPA ;
