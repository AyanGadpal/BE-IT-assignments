

CREATE TABLE emp
(
    eid int not null PRIMARY key,
    name varchar(20) not null ,
    desi VARCHAR(20) not null ,
    sal FLOAT not null
);

CREATE TABLE dept
(
    did int not null PRIMARY key,
    name varchar(20) not null ,
    LOC VARCHAR(20) not null
);

CREATE TABLE project
(
    pid int not null PRIMARY key,
    name varchar(20) not null,
    status varchar(20) not null
);

CREATE TABLE empDept
(
  eid int,
  did int
);

CREATE TABLE empProject
(
  eid int not null,
  pid int not null,
  FOREIGN key (eid) references emp(eid),
  FOREIGN key (pid) references project(pid)
);

alter table empDept
add FOREIGN KEY (eid) references emp(eid);

alter table empDept
add FOREIGN KEY (did) references dept(did);

ALTER TABLE empDept
ADD CONSTRAINT pri_key
PRIMARY KEY (eid,did)


insert into emp(eid,name,desi,sal) 
values (1,"Ayan","Manager",20000),
 (2,"Kalpit","Devloper",20000),
 (3,"Maniya","Manager",20000),
 (4,"Aniya","Devloper",20000),
 (5,"Manas","Tester",20000),
 (6,"Manasi","Tester",20000),
 (7,"Deva","Manager",20000),
 (8,"Dhananjay","Chaivala",20);

insert into dept(did,name,LOC) 
values (1,"IT","Pune"),
 (2,"INVENTORY","Pune"),
 (3,"MARKETING","Nagpur");

insert into project(pid,name,status) 
values (1,"blood","complete"),
 (2,"Shopping","incomplete"),
 (3,"Eannapurna","incomplete");


insert into empDept(eid,did) 
values 
(1,3),(2,3),(8,3),
(7,2),(4,2),(5,2),
(3,1),(6,1);

insert into empProject(eid,pid) 
values 
(1,1),(7,1),(5,1),
(8,2),(4,2),(5,2),
(3,3),(6,3);

select * from emp where eid in
(
     select eid from empDept as T,dept as D 
     where T.did = D.did and LOC = "Pune" 
     AND D.name = "INVENTORY"
);

SELECT * from emp as E 
INNER join empDept as ED on E.eid = ED.eid
INNER JOIN dept as D on ED.did = D.did
where D.LOC = "Pune" 
AND D.name = "INVENTORY";

select E.name from emp as E where eid in
(
     select eid 
     from empProject as T,project as P 
     where T.pid = P.pid and P.name = "blood"
);

SELECT * FROM emp AS E 
INNER JOIN empProject AS EP ON E.eid = EP.eid
INNER JOIN project AS P ON EP.pid = P.pid
where P.name = "blood" ;

select * from emp where desi = "Manager" AND
eid in
(
     select eid from empDept as T,dept as D 
     where T.did = D.did 
     and D.name = "MARKETING"
);


SELECT * from emp as E 
INNER join empDept as ED on E.eid = ED.eid
INNER JOIN dept as D on ED.did = D.did
where AND E.desi = "Manager";