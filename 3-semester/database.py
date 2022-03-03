import sqlite3

class DB:
    def __init__(self):
        self.conn = sqlite3.connect('music1.db')  # Создаем соединение с базой данных
        self.c = self.conn.cursor()  # создаем курсор - это специальный объект который делает запросы и получает их результаты

    def execute_query(self, query):
        try:
            self.c.execute(query)
            self.conn.commit()
        except:
            print('Failed to execute query:\n ', query)

    def add_artist(self, Artist):
        create_queryArtist = f"""INSERT INTO artist(artist_name) SELECT ("{Artist}") WHERE NOT EXISTS (SELECT artist_name FROM artist
				WHERE artist_name = ("{Artist}"));"""
        self.execute_query(create_queryArtist)

    def add_albumTitle(self, AlbumTitle):
        create_queryAlbum = f"""INSERT INTO album(album_title) SELECT ("{AlbumTitle}") WHERE NOT EXISTS (SELECT album_title FROM album
				WHERE album_title = ("{AlbumTitle}"));"""
        self.execute_query(create_queryAlbum)

    def add_genre(self, Genre):
        create_queryGenre = f"""INSERT INTO genre (genre_title) SELECT ("{Genre}") WHERE NOT EXISTS (SELECT genre_title FROM genre
				WHERE genre_title = ("{Genre}"));"""
        self.execute_query(create_queryGenre)

    def displayArtist(self, target_field, Artist, index):
        query = f"""
				SELECT * FROM artist
				WHERE "{target_field}" = "{Artist}";"""
        get_id_Artist = self.c.execute(query)
        return get_id_Artist.fetchall()[0][index]

    def displayAlbumTitle(self, target_field, AlbumTitle, index):
        query = f"""SELECT * FROM album WHERE "{target_field}" = "{AlbumTitle}";"""
        get_id_Album = self.c.execute(query)
        return get_id_Album.fetchall()[0][index]

    def displayGenre(self, target_field, Genre, index):
        query = f"""SELECT * FROM genre WHERE "{target_field}" = "{Genre}";"""
        get_id_Genre = self.c.execute(query)
        return get_id_Genre.fetchall()[0][index]

    def insert_data(self, Artist, Label, AlbumTitle, Genre, Rating):

        self.add_artist(Artist)
        self.add_albumTitle(AlbumTitle)
        self.add_genre(Genre)

        id_artist = self.displayArtist('artist_name', Artist, 0)
        id_album = self.displayAlbumTitle('album_title', AlbumTitle, 0)
        id_genre = self.displayGenre('genre_title', Genre, 0)

        q = f"""INSERT INTO release (artist_id, label, album_id, genre_id, rating)
		VALUES ({id_artist}, '{Label}', {id_album}, {id_genre}, '{Rating}')"""
        self.execute_query(q)

    def insert_records(self, records):
        for record in records:
            self.insert_data(record)
        self.conn.commit()

    def get_all_release(self):
        query = """
		SELECT release.id, artist.artist_name,  label, album.album_title, genre.genre_title, rating FROM release
	 	JOIN artist
	 	ON release.artist_id = artist.artist_id
	 	JOIN album
	 	ON release.album_id = album.album_id
	 	JOIN genre
		ON release.genre_id = genre.genre_id"""
        return self.execute_query(query)

    def get_all_release_searchD(self):
        query = """
				SELECT release.id, artist.artist_name, album.album_title, label, genre.genre_title, rating FROM release
			 	JOIN artist
			 	ON release.artist_id = artist.artist_id
			 	JOIN album
			 	ON release.album_id = album.album_id
			 	JOIN genre
				ON release.genre_id = genre.genre_id
			 	ORDER BY Rating DESC"""
        return self.execute_query(query)

    def get_all_release_searchA(self):
        query = """
				SELECT release.id, artist.artist_name, album.album_title, label, genre.genre_title, rating FROM release
			 	JOIN artist
			 	ON release.artist_id = artist.artist_id
			 	JOIN album
			 	ON release.album_id = album.album_id
			 	JOIN genre
				ON release.genre_id = genre.genre_id
			 	ORDER BY Rating ASC"""
        return self.execute_query(query)
