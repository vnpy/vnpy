use BackTest;

create table TB_Trade
(
    Id varchar(255),
    symbol varchar(20),
    orderRef varchar(20),
    tradeID varchar(20),
    direction varchar(10),
    offset varchar(10),
    price float,
    volume int

);