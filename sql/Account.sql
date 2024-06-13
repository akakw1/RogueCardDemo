create table Account(
    id int primary key auto_increment,
    username varchar(255) not null,
    password varchar(255) not null,
    email varchar(255) not null,
    phone varchar(255) not null,
    create_time timestamp not null default current_timestamp on update current_timestamp
);