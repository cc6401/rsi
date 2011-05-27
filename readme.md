1. Crear base de datos "rsi"
2. Crear usuario `rsi` con password `rsi123` para la base de datos
   1. Entrar a mysql como root
   2. Agregar el usuario:
      1. `mysql> use mysql`
      2. `mysql> create user rsi@localhost identified by "rsi123";`
      3. `mysql> grant all privileges on rsi.* to rsi with grant option;`
3. Importar el último sql en la base de datos, usando
   `mysql -u rsi -p rsi < 20110*_rsi.sql`

Para entrar como administrador:
1. Acc No: `1`
2. Password: `password`

