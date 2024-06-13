create table Version(
    version varchar(255) primary key,
    create_time timestamp not null default current_timestamp,
    update_time timestamp not null default current_timestamp on update current_timestamp
);