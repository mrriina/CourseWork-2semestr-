from database import DB

table_allNewRelease = """
			CREATE TABLE IF NOT EXISTS release
			 (id INTEGER PRIMARY KEY, album_id INTEGER, artist_id INTEGER, label TEXT, genre_id INTEGER, rating INTEGER);
			 """

table_Artist = """CREATE TABLE IF NOT EXISTS artist(
				artist_id INTEGER PRIMARY KEY,
				artist_name TEXT);"""

table_Album = """CREATE TABLE IF NOT EXISTS album(
				album_id INTEGER PRIMARY KEY,
				album_title TEXT);"""

table_Genre = """CREATE TABLE IF NOT EXISTS genre(
				genre_id INTEGER PRIMARY KEY,
				genre_title TEXT);"""

insert_table_Genre = """INSERT INTO genre(genre_title)
					VALUES ('Avant-Garde'), ('Blues'), ('Children'), ('Classical'), ('Comedy/Spoken'), 
					('Country'), ('Easy Listening'), ('Electronic'), ('Folk'), ('Holiday'), ('International'), 
					('Jazz'), ('Latin'), ('New Age'), ('Pop/Rock'), ('R&B'), ('Rap'), ('Reggae'), ('Religious'), 
					('Stage&Screen'), ('Vocal')"""

insert_table_Album = """INSERT INTO album(album_title)
					VALUES ('If'), ('Strictly Off the Love'), ('Seni Buralardan Kurtarırım'), ('Arcade Versions of Studio Ghibli'),
					('Fool Again'), ('Love Letters Nine Through Six'), ('Back Home'), ('Passion & Pain'), ('Little Things'),
					('Blueprint'), ('Talking Head'), ('Numb'), ('Live It Up'), ('Bem Jhonson'), ('Alpine Drive'), 
					('Observatory'), ('Lit'), ('Competition'), ('The Inner Side'), ('Age of Wolves')"""

insert_table_Artist = """INSERT INTO artist(artist_name)
					VALUES ('199X'), ('2xx Pheno'), ('8EIGHT'), ('A1 Hunnit'), ('A Great Big World'), ('Adonis Maia'), ('Aero'),
					 ('Agarthic'), ('Aiwabeatz'), ('Aisha'), ('ALLBLACK'), ('Blanco Balling')"""

insert_table_allNewRelease = """INSERT INTO release(album_id, artist_id, label, genre_id, rating)
								VALUES (2, 3, 'Yin Yang Media', 20, 5), (4, 2, 'Bighit', 15, 8), (19, 12, 'BBI', 6, 9), 
								(12, 10, 'Flip', 15, 10), (10, 11, 'Sub Pop', 15, 1), (9, 3, 'Cryo Chamber', 12, 4), (7, 8, 'Beatclap',17, 5),
								(8, 7, 'The Jet Set', 8, 6), (6, 6, 'Earache', 5, 7), (5, 1, 'M & O Music', 21, 7),
								(1, 4, 'Erato', 20, 7), (3, 5, 'RCA', 17, 8)"""

def create_table():
	db = DB()
	db.execute_query(table_allNewRelease)
	db.execute_query(table_Artist)
	db.execute_query(table_Album)
	db.execute_query(table_Genre)

def init_table():
	db = DB()
	db.execute_query(insert_table_Album)
	db.execute_query(insert_table_Artist)
	db.execute_query(insert_table_Genre)
	db.execute_query(insert_table_allNewRelease)

if __name__ == '__main__':
	create_table()
	init_table()