prompt #---------------------#
prompt #- Pomocne procedury -#
prompt #---------------------#

create or replace procedure SMAZ_VSECHNY_TABULKY AS
-- pokud v logu bude uvedeno, ze nektery objekt nebyl zrusen, protoze na nej jiny jeste existujici objekt stavi, spust proceduru opakovane, dokud se nezrusi vse
begin
  for iRec in 
    (select distinct OBJECT_TYPE, OBJECT_NAME,
      'drop '||OBJECT_TYPE||' "'||OBJECT_NAME||'"'||
      case OBJECT_TYPE when 'TABLE' then ' cascade constraints purge' else ' ' end as PRIKAZ
    from USER_OBJECTS where OBJECT_NAME not in ('SMAZ_VSECHNY_TABULKY', 'VYPNI_CIZI_KLICE', 'ZAPNI_CIZI_KLICE', 'VYMAZ_DATA_VSECH_TABULEK')
    ) loop
        begin
          dbms_output.put_line('Prikaz: '||irec.prikaz);
        execute immediate iRec.prikaz;
        exception
          when others then dbms_output.put_line('NEPOVEDLO SE!');
        end;
      end loop;
end;
/

create or replace procedure VYPNI_CIZI_KLICE as 
begin
  for cur in (select CONSTRAINT_NAME, TABLE_NAME from USER_CONSTRAINTS where CONSTRAINT_TYPE = 'R' ) 
  loop
    execute immediate 'alter table '||cur.TABLE_NAME||' modify constraint "'||cur.CONSTRAINT_NAME||'" DISABLE';
  end loop;
end VYPNI_CIZI_KLICE;
/


create or replace procedure ZAPNI_CIZI_KLICE as 
begin
  for cur in (select CONSTRAINT_NAME, TABLE_NAME from USER_CONSTRAINTS where CONSTRAINT_TYPE = 'R' ) 
  loop
    execute immediate 'alter table '||cur.TABLE_NAME||' modify constraint "'||cur.CONSTRAINT_NAME||'" enable validate';
  end loop;
end ZAPNI_CIZI_KLICE;
/

create or replace procedure VYMAZ_DATA_VSECH_TABULEK is
begin
  -- Vymazat data vsech tabulek
  VYPNI_CIZI_KLICE;
  for v_rec in (select distinct TABLE_NAME from USER_TABLES)
  loop
    execute immediate 'truncate table '||v_rec.TABLE_NAME||' drop storage';
  end loop;
  ZAPNI_CIZI_KLICE;
  
  -- Nastavit vsechny sekvence od 1
  for v_rec in (select distinct SEQUENCE_NAME  from USER_SEQUENCES)
  loop
    execute immediate 'alter sequence '||v_rec.SEQUENCE_NAME||' restart start with 1';
  end loop;
end VYMAZ_DATA_VSECH_TABULEK;
/

prompt #------------------------#
prompt #- Zrusit stare tabulky -#
prompt #------------------------#

exec SMAZ_VSECHNY_TABULKY;


CREATE TABLE branch (
    b_id         INTEGER NOT NULL,
    b_contract   VARCHAR2(30),
    pay_date     DATE NOT NULL,
    b_requis     VARCHAR2(30) NOT NULL,
    b_address    VARCHAR2(30 CHAR) NOT NULL
);

ALTER TABLE branch ADD CONSTRAINT branch_pk PRIMARY KEY ( b_id );

CREATE TABLE customer (
    c_id          INTEGER NOT NULL,
    c_fname       CHAR(40 CHAR) NOT NULL,
    c_age         INTEGER,
    c_phone       INTEGER NOT NULL,
    c_birthdate   DATE NOT NULL,
    c_email       VARCHAR2(40) NOT NULL
);

ALTER TABLE customer ADD CONSTRAINT customer_pk PRIMARY KEY ( c_id );

CREATE TABLE employee (
    employee_id   INTEGER NOT NULL,
    e_fullname    CHAR(40 CHAR) NOT NULL
);

ALTER TABLE employee ADD CONSTRAINT employee_pk PRIMARY KEY ( employee_id );

CREATE TABLE goods (
    g_id            INTEGER NOT NULL,
    g_name          CHAR(30 CHAR) NOT NULL,
    receipt_price   NUMBER NOT NULL,
    sold_price      NUMBER NOT NULL,
    receipt_date    DATE NOT NULL,
    sold_date       DATE NOT NULL
);

ALTER TABLE goods ADD CONSTRAINT goods_pk PRIMARY KEY ( g_id );

CREATE TABLE relation_11 (
    branch_b_id   INTEGER NOT NULL,
    goods_g_id    INTEGER NOT NULL
);

ALTER TABLE relation_11 ADD CONSTRAINT relation_11_pk PRIMARY KEY ( goods_g_id );

CREATE TABLE reservation (
    reserv_id       INTEGER NOT NULL,
    reserv_date     DATE,
    b_id            INTEGER NOT NULL,
    employee_id     INTEGER NOT NULL,
    service_price   NUMBER NOT NULL,
    c_id            INTEGER NOT NULL,
    service_id      INTEGER NOT NULL
);

ALTER TABLE reservation ADD CONSTRAINT reservation_pk PRIMARY KEY ( reserv_id );

CREATE TABLE salary (
    salary_id     INTEGER NOT NULL,
    salary_date   DATE NOT NULL,
    salary_sum    NUMBER NOT NULL,
    employee_id   INTEGER NOT NULL
);

ALTER TABLE salary ADD CONSTRAINT salary_pk PRIMARY KEY ( salary_id );

CREATE TABLE schedule (
    sched_date    DATE NOT NULL,
    employee_id   INTEGER NOT NULL,
    sched_id      INTEGER NOT NULL
);

ALTER TABLE schedule ADD CONSTRAINT schedule_pk PRIMARY KEY ( sched_id );

CREATE TABLE service (
    service_id      INTEGER NOT NULL,
    service_type    CHAR(30) NOT NULL,
    service_price   NUMBER NOT NULL
);

ALTER TABLE service ADD CONSTRAINT service_pk PRIMARY KEY ( service_id );

ALTER TABLE relation_11
    ADD CONSTRAINT relation_11_branch_fk FOREIGN KEY ( branch_b_id )
        REFERENCES branch ( b_id );

ALTER TABLE relation_11
    ADD CONSTRAINT relation_11_goods_fk FOREIGN KEY ( goods_g_id )
        REFERENCES goods ( g_id );

ALTER TABLE reservation
    ADD CONSTRAINT reservation_branch_fk FOREIGN KEY ( b_id )
        REFERENCES branch ( b_id );

ALTER TABLE reservation
    ADD CONSTRAINT reservation_customer_fk FOREIGN KEY ( c_id )
        REFERENCES customer ( c_id );

ALTER TABLE reservation
    ADD CONSTRAINT reservation_employee_fk FOREIGN KEY ( employee_id )
        REFERENCES employee ( employee_id );

ALTER TABLE reservation
    ADD CONSTRAINT reservation_service_fk FOREIGN KEY ( service_id )
        REFERENCES service ( service_id );

ALTER TABLE salary
    ADD CONSTRAINT salary_employee_fk FOREIGN KEY ( employee_id )
        REFERENCES employee ( employee_id );

ALTER TABLE schedule
    ADD CONSTRAINT schedule_employee_fk FOREIGN KEY ( employee_id )
        REFERENCES employee ( employee_id );

CREATE SEQUENCE customer_c_id_seq START WITH 1 NOCACHE ORDER;

CREATE OR REPLACE TRIGGER customer_c_id_trg BEFORE
    INSERT ON customer
    FOR EACH ROW
    WHEN ( new.c_id IS NULL )
BEGIN
    :new.c_id := customer_c_id_seq.nextval;
END;
/



-- Oracle SQL Developer Data Modeler Summary Report: 
-- 
-- CREATE TABLE                             9
-- CREATE INDEX                             0
-- ALTER TABLE                             17
-- CREATE VIEW                              0
-- ALTER VIEW                               0
-- CREATE PACKAGE                           0
-- CREATE PACKAGE BODY                      0
-- CREATE PROCEDURE                         0
-- CREATE FUNCTION                          0
-- CREATE TRIGGER                           1
-- ALTER TRIGGER                            0
-- CREATE COLLECTION TYPE                   0
-- CREATE STRUCTURED TYPE                   0
-- CREATE STRUCTURED TYPE BODY              0
-- CREATE CLUSTER                           0
-- CREATE CONTEXT                           0
-- CREATE DATABASE                          0
-- CREATE DIMENSION                         0
-- CREATE DIRECTORY                         0
-- CREATE DISK GROUP                        0
-- CREATE ROLE                              0
-- CREATE ROLLBACK SEGMENT                  0
-- CREATE SEQUENCE                          1
-- CREATE MATERIALIZED VIEW                 0
-- CREATE SYNONYM                           0
-- CREATE TABLESPACE                        0
-- CREATE USER                              0
-- 
-- DROP TABLESPACE                          0
-- DROP DATABASE                            0
-- 
-- REDACTION POLICY                         0
-- 
-- ORDS DROP SCHEMA                         0
-- ORDS ENABLE SCHEMA                       0
-- ORDS ENABLE OBJECT                       0
-- 
-- ERRORS                                   0
-- WARNINGS                                 0
