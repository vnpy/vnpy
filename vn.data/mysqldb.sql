use BackTest;

CREATE TABLE `TB_Trade` (
  `Id` varchar(255) DEFAULT NULL,
  `symbol` varchar(20) DEFAULT NULL,
  `orderRef` int(11) DEFAULT '0',
  `tradeID` int(11) DEFAULT '0',
  `direction` tinyint(4) DEFAULT NULL,
  `offset` tinyint(4) DEFAULT NULL,
  `price` float DEFAULT NULL,
  `volume` int(11) DEFAULT NULL,
  `tradeTime` datetime DEFAULT NULL,
  `amount` float DEFAULT '0',
  `fee` float DEFAULT '0',
  `profit` float DEFAULT '0',
  `profitRate` float DEFAULT '0'
)

create table TB_Bar
(
    Id varchar(255),
    symbol varchar(20),
    open float,
    high float,
    low float,
    close float,
    date date,
    time time,
    datetime datetime,
    volume long,
    openInterest long

);

create table TB_Ema
(
    Id varchar(255),
    symbol varchar(20),
    fastEMA float,
    slowEMA float,
    date date,
    time time,
    datetime datetime

);

delete from TB_Trade;
delete from TB_Bar;
delete from TB_Ema;
