create table accounts
(
userId int auto_increment primary key,
userName varchar(100) unique,
passWord varchar(100)
);

create table players
(
userId int ,
playerId int auto_increment primary key,
nickName varchar(100),
foreign key(userId) references accounts(userId)
);

create table chest
(
playerId int,
itemId int,
quantity int,
foreign key(playerId) references players(playerId)
);
