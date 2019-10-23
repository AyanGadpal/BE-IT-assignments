create table customer(
    cid int not null auto_increment PRIMARY KEY,
    name VARCHAR(20) not NULL,
    contact CHAR(10) not null
);

CREATE TABLE product
(
    pid int not null auto_increment primary key,
    name varchar(20) not null,
    stock int not null,
    price float not null
);

CREATE table orderCustomer(
    oid int auto_increment PRIMARY key,
    cid int not NULL,
    total_price float,
    foreign key(cid) REFERENCES customer(cid)
);

CREATE table orderProduct(
     oid int not null,
     pid int not null,
     quantity int not null,
     foreign key(oid) REFERENCES orderCustomer(oid),
     foreign key(pid) REFERENCES product(pid),
     PRIMARY key(oid,pid)
)


	
insert into customer(oid,cid) values(NULL,"shweta","8988336239"),
(NULL,"Diksha","9307337139"),(NULL,"Man Asi","9305566739"),
(NULL,"Dhananjay","9303344135");

insert into product(pid,name,stock,price) values(NULL,"Chai",30,10),
(NULL,"Idli",20,20),(NULL,"Medu Vada",10,30),
(NULL,"Poha",10,30);



DELIMITER $$

CREATE TRIGGER triiger after insert on orderProduct
FOR each row 
begin 
UPDATE product set stock = stock - new.quantity where pid = new.pid; 
end $$

DELIMITER ;

	
insert into orderCustomer(oid,cid) values(NULL,1);
insert into orderProduct(oid,pid,quantity) values(1,1,2);
