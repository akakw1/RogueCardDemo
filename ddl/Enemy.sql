create table Enemy(
    id int primary key auto_increment,
    name varchar(255) not null,
    MaxHp int not null,
    version varchar(255) not null,
    foreign key(version) references Version(version)
);