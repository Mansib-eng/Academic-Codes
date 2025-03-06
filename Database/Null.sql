/*
 In SQL There are 3 boolean Values -> True , False and Unknown
 Unknown is used for 'Null'
 Where and when is used for 'True'

 Unknown(U), True(T), False(F)
 T | U = T
 U | U = U
 F | U = U
 U | T = T
 U | F = U

 T & U = U
 U & T = U
 F & U = F
 U & F = F
 U & U = U
 */

 Use university ;
UPDATE department
set `Number of teachers` = 25
Where Budget > 300000 ;                # Can't update 'Null'

UPDATE department
set Budget = 200000
where `Number of teachers` between 20 and 30 ;  # Now can Update 'Null'

SELECT ID from student
where Department = 'Null' ;    # It will show nothing

SELECT ID from student
where Department is NULL ;     # By using 'IS' it can work with Null value