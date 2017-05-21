voici ma base de donnée :
```SQL
DROP TABLE jouer;
DROP TABLE partie;
DROP TABLE joueur;

CREATE TABLE joueur
	( email VARCHAR2 (60),
	  pseudo VARCHAR2 (30),
	  dateNaissance DATE,
	  CONSTRAINT pk_pseudo PRIMARY KEY( pseudo),
	  CONSTRAINT ck_email CHECK ( email IS NOT NULL ),
	  CONSTRAINT ck_dateNaissance CHECK ( dateNaissance IS NOT NULL )
);

CREATE TABLE partie 
	(id_partie NUMBER(5),
	 tailleGrille NUMBER(2),
	 dateCreation DATE,
	 joueur1 VARCHAR2 (30),
	 etatJ1 VARCHAR2(20),
	 couleurJ1 VARCHAR2(6),
	 joueur2 VARCHAR2(30),
	 CONSTRAINT pk_id_partie PRIMARY KEY ( id_partie),
	 CONSTRAINT ck_tailleGrille CHECK ( tailleGrille IS NOT NULL),
	 CONSTRAINT ck_dateCreation CHECK ( dateCreation IS NOT NULL ),
	 CONSTRAINT fk_joueur1 FOREIGN KEY ( joueur1 ) REFERENCES joueur ( pseudo),
	 CONSTRAINT ck_etatJ1 CHECK ( etatJ1 IN ('non termine','gagne','perdu','abondonné')),
	 CONSTRAINT ck_couleurJ1 CHECK ( couleurJ1 IN ('noir','blanc')),
	 CONSTRAINT fk_joueur2 FOREIGN KEY ( joueur2 ) REFERENCES joueur ( pseudo)
);

CREATE TABLE jouer
	(numeroDuCoup NUMBER(4),
	 coup NUMBER(4),
	 partie NUMBER(5),
	 CONSTRAINT pk_numeroDuCoup PRIMARY KEY (numeroDuCoup , partie),
	 CONSTRAINT fk_partie FOREIGN KEY ( partie) REFERENCES partie (id_partie)
);
	 
@exemple de remplissage

INSERT INTO joueur(email,pseudo,dateNaissance) VALUES ('pierreselebran@yahoo.fr','FOXcard','31-01-1997');
INSERT INTO joueur(email,pseudo,dateNaissance) VALUES ('ajy.roussel@gmail.com','MisterPupuce','13-12-1997');
INSERT INTO joueur(email,pseudo,dateNaissance) VALUES ('hugo.rous@gmail.com','Arterios','11-12-1997');

INSERT INTO partie(id_partie,tailleGrille,dateCreation,joueur1,etatJ1,couleurJ1,joueur2) VALUES (25406,5,'21-05-2017','FOXcard','gagne','blanc','Arterios');
INSERT INTO partie(id_partie,tailleGrille,dateCreation,joueur1,etatJ1,couleurJ1,joueur2) VALUES (13456,5,'21-05-2017','MisterPupuce','non termine','noir','Arterios');
INSERT INTO partie(id_partie,tailleGrille,dateCreation,joueur1,etatJ1,couleurJ1,joueur2) VALUES (65420,11,'19-05-2017','MisterPupuce','perdu','blanc','FOXcard');
INSERT INTO partie(id_partie,tailleGrille,dateCreation,joueur1,etatJ1,couleurJ1,joueur2) VAlUES (12045,7,'18-05-2017','Arterios','abondonné','blanc','FOXcard');

INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (1,16,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (2,8,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (3,13,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (4,2,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (5,12,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (6,7,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (7,9,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (8,15,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (9,20,25406);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (1,8,13456);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (1,16,12045);
INSERT INTO jouer (numeroDuCoup,coup,partie) VALUES (1,12,65420);


@exemple de requete 
@retrouver les parties effectuées par un joueur à une date donnée :
SELECT id_partie FROM partie,joueur WHERE dateCreation = '21-05-2017' AND pseudo = 'FOXcard';
@retrouver toutes les partie affectué par un joueur
SELECT DISTINCT id_partie FROM partie,joueur WHERE joueur1 = 'FOXcard' OR joueur2 = 'FOXcard';
@retrouver les parties gagnées par un joueur
SELECT DISTINCT id_partie FROM partie,joueur WHERE ( joueur1 = 'FOXcard' AND etatJ1='gagne' ) or ( joueur2 = 'FOXcard' AND etatJ1='perdu');
@retrouver les parties abandonnées auxquelles à participé un joueur
SELECT DISTINCT id_partie FROM partie , joueur WHERE pseudo = 'FOXcard' AND etatJ1='abondonné';
@retrouver les joueurs rencontrés par un joueur donné
SELECT DISTINCT pseudo FROM partie, joueur WHERE (joueur1 = 'FOXcard' OR joueur2= 'FOXcard') AND pseudo != 'FOXcard';
@retrouver les parties débutée par un coup donné
SELECT DISTINCT id_partie FROM jouer , partie WHERE numeroDuCoup = 1 AND coup = 16;
```