insert into student
# VALUES (null , 'Tipu' , 'EEE')  # If we want to Null the 1st element but it will show error..Because ID is Primary Key
VALUES ('2020441010','Tipu',Null) ;   # It will work

INSERT INTO department(name, `number of teachers`)   # We want Budget will be Null
VALUES ('CEP',20),
       ('PHY',25),
       ('CHEM',30)
