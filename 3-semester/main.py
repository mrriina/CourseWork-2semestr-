import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from database import DB

class Main(tk.Frame):
	def __init__(self, root):
		super().__init__(root)
		self.ascending_sort = False
		self.init_main()
		self.db = DB()
		self.view_records()

	def init_main(self):
		toolbar = tk.Frame(bg='#d7d8e0', bd=2)
		toolbar.pack(side=tk.TOP, fill=tk.X)

		self.add_img = tk.PhotoImage(file="C:\\Users\\Марина\\Desktop\\Univers\\3 semestr\\YaP\\CourseWork\\add_image.png")
		btn_open_dialog = tk.Button(toolbar, command=self.open_dialog, bg='#d7d8e0', bd=0,
									compound=tk.TOP, image=self.add_img)
		btn_open_dialog.pack(side=tk.LEFT, padx=90)

		self.update_img = tk.PhotoImage(file="C:\\Users\\Марина\\Desktop\\Univers\\3 semestr\\YaP\\CourseWork\\edit_image.png")
		btn_edit_dialog = tk.Button(toolbar, bg='#d7d8e0', bd=0, command=self.open_update_dialog,
									compound=tk.TOP, image=self.update_img)

		btn_edit_dialog.pack(side=tk.LEFT, padx=90)

		self.delete_img = tk.PhotoImage(file="C:\\Users\\Марина\\Desktop\\Univers\\3 semestr\\YaP\\CourseWork\\del_image.png")
		btn_delete = tk.Button(toolbar, bg='#d7d8e0', bd=0, command=self.delete_records,
							   compound=tk.TOP, image=self.delete_img)
		btn_delete.pack(side=tk.LEFT, padx=90)

		self.search_img = tk.PhotoImage(file="C:\\Users\\Марина\\Desktop\\Univers\\3 semestr\\YaP\\CourseWork\\search_image.png")
		btn_search = tk.Button(toolbar, bg='#d7d8e0', bd=0, command=self.open_search_dialog,
							   compound=tk.TOP, image=self.search_img)
		btn_search.pack(side=tk.RIGHT, padx=90)
		self.refresh_img = tk.PhotoImage(file="C:\\Users\\Марина\\Desktop\\Univers\\3 semestr\\YaP\\CourseWork\\refresh_image.png")
		btn_refresh = tk.Button(toolbar, bg='#d7d8e0', bd=0, command=self.view_records,
								compound=tk.TOP, image=self.refresh_img)
		btn_refresh.pack(side=tk.RIGHT, padx=90)

		self.sort_img = tk.PhotoImage(file="C:\\Users\\Марина\\Desktop\\Univers\\3 semestr\\YaP\\CourseWork\\sort_image.png")
		btn_sorting = tk.Button(toolbar, bg='#d7d8e0', bd=0,
								command=self.sort_items, compound=tk.TOP, image=self.sort_img)
		btn_sorting.pack(side=tk.RIGHT, padx=90)

		self.tree = ttk.Treeview(self, columns=('ID', 'Artist', 'Label', 'AlbumTitle', 'Genre', 'Rating'),
								 height=15, show='headings')
		self.tree.column("ID", width=80, anchor=tk.CENTER)
		self.tree.column("Artist", width=390, anchor=tk.CENTER)
		self.tree.column("Label", width=250, anchor=tk.CENTER)
		self.tree.column("AlbumTitle", width=250, anchor=tk.CENTER)
		self.tree.column("Genre", anchor=tk.CENTER)
		self.tree.column("Rating", width=150, anchor=tk.CENTER)

		self.tree.heading("ID", text='ID')  # настраиваем имя заголовка
		self.tree.heading("Artist", text='Artist')
		self.tree.heading("Label", text='Label')
		self.tree.heading("AlbumTitle", text='Album Title')
		self.tree.heading("Genre", text='Genre')
		self.tree.heading("Rating", text='Rating')

		self.tree.pack(side=tk.LEFT)

		scroll = tk.Scrollbar(self, command=self.tree.yview)
		scroll.pack(side=tk.LEFT, fill=tk.Y)
		self.tree.configure(yscrollcommand=scroll.set)

	def sort_items(self):
		if self.ascending_sort:
			self.descending()
		else:
			self.ascending()
		self.ascending_sort = not self.ascending_sort

	def descending(self):
		self.db.get_all_release_searchD()
		self.display_items(self.db.c.fetchall())

	def ascending(self):
		self.db.get_all_release_searchA()
		self.display_items(self.db.c.fetchall())

	def records(self, Artist, Label, AlbumTitle, Genre, Rating):
		self.db.insert_data(Artist, Label, AlbumTitle, Genre, Rating)
		self.view_records()

	def update_record(self, Artist, Label, AlbumTitle, Genre, Rating):

		self.db.c.execute(
			f''' DELETE FROM genre WHERE genre_id Not In(SELECT genre_id FROM release GROUP BY genre_id) ''')

		self.db.c.execute(
			f''' DELETE FROM artist WHERE artist_id Not In(SELECT artist_id FROM release GROUP BY artist_id) ''')

		self.db.c.execute(
			f''' DELETE FROM album WHERE album_id Not In(SELECT album_id FROM release GROUP BY album_id) ''')

		self.db.add_artist(Artist)
		self.db.add_albumTitle(AlbumTitle)
		self.db.add_genre(Genre)

		self.db.c.execute(
			f'''UPDATE release SET artist_id = (SELECT artist_id FROM artist WHERE  artist_name = "{Artist}")
		            WHERE release.id = {self.tree.set(self.tree.selection()[0], '#1')} ''')

		self.db.c.execute(
			f'''UPDATE release SET album_id = (SELECT album_id FROM album WHERE  album_title = "{AlbumTitle}")
		          WHERE release.id = {self.tree.set(self.tree.selection()[0], '#1')} ''')

		self.db.c.execute(
			f'''UPDATE release SET genre_id = (SELECT genre_id FROM genre WHERE genre_title = "{Genre}")
		    WHERE release.id = {self.tree.set(self.tree.selection()[0], '#1')} ''')

		self.db.c.execute(
			f'''UPDATE release SET label= "{Label}",  rating="{Rating}" WHERE id={self.tree.set(self.tree.selection()[0], '#1')}''')

		# selection-возвращает список из уникальных id выделенных записей таблицы
		self.db.conn.commit()
		self.view_records()

	def view_records(self):
		self.db.get_all_release()
		self.display_items(self.db.c.fetchall())

	def display_items(self, items):

		[self.tree.delete(i) for i in self.tree.get_children()]

		for item_index in range(len(items)):
			items[item_index] = list(items[item_index])
			try:
				items[item_index][-1] = '✰' * int(items[item_index][-1])
			except:
				continue
		[self.tree.insert('', 'end', values=row) for row in items]

	def display(self, items):
		[self.tree.delete(i) for i in self.tree.get_children()]
		for row in items:
			new = []
			new.append(row[0])
			new.append(self.db.displayArtist('artist_id', row[2], 1))
			new.append(row[3])
			new.append(self.db.displayAlbumTitle('album_id', row[1], 1))
			new.append(self.db.displayGenre('genre_id', row[4], 1))
			new.append(row[5])
			new[-1] = '✰' * int(new[-1])
			self.tree.insert('', 'end', values=new)

	def delete_records(self):
		if len(self.tree.selection()) == 0:
			messagebox.showinfo("Error", "Select the record in the table")
		else:
			for selection_item in self.tree.selection():
				self.db.c.execute('''DELETE FROM release WHERE id=?''', (self.tree.set(selection_item, '#1'),))
			self.db.conn.commit()
			self.view_records()

	def search_records(self, target_field, search_value):
		if target_field == 'Artist':
			self.db.c.execute(f'''SELECT * FROM release
							JOIN artist
							WHERE (artist.artist_name = "{search_value}" and release.artist_id = artist.artist_id) ''')
		elif target_field == 'AlbumTitle':
			self.db.c.execute(f'''SELECT * FROM release
							JOIN album
							WHERE (album.album_title = "{search_value}" and release.album_id = album.album_id) ''')
		elif target_field == 'Genre':
			self.db.c.execute(f'''SELECT * FROM release
							JOIN genre
							WHERE (genre.genre_title = "{search_value}" and release.genre_id = genre.genre_id) ''')
		elif target_field == 'Label':
			self.db.c.execute(f'''SELECT * FROM release WHERE label LIKE  "{search_value}"''')
		else:
			self.db.c.execute(f'''SELECT * FROM release WHERE rating LIKE  "{search_value}"''')
		self.display(self.db.c.fetchall())

	def open_dialog(self):
		Child()

	def open_update_dialog(self):
		if len(self.tree.selection()) == 0:  # выделена ли строка
			messagebox.showinfo("Error", "Select the record in the table")
		elif len(self.tree.selection()) > 1:
			messagebox.showinfo("Error", "Select one record in the table")
		else:
			Update()

	def open_search_dialog(self):
		Search()

class Child(tk.Toplevel):
	def __init__(self):
		super().__init__(root)
		self.init_child()
		self.view = app

	def init_child(self):
		self.title('Add new music')
		self.geometry('400x250+400+300')
		self.resizable(False, False)

		label_artist = tk.Label(self, text='Artist:')  # отображения какой-либо надписи без возможности редактирования
		label_artist.place(x=50, y=50)
		label_label = tk.Label(self, text='Label:')
		label_label.place(x=50, y=80)
		label_albumTitle = tk.Label(self, text='Album Title:')
		label_albumTitle.place(x=50, y=110)
		label_selectGenre = tk.Label(self, text='Genre:')
		label_selectGenre.place(x=50, y=140)
		label_rating = tk.Label(self, text='Rating:')
		label_rating.place(x=50, y=170)

		self.entry_artist = ttk.Entry(self)  # позволяет пользователю ввести одну строку текста (поле ввода)
		self.entry_artist.place(x=200, y=50)

		self.entry_label = ttk.Entry(self)
		self.entry_label.place(x=200, y=80)

		self.entry_albumTitle = ttk.Entry(self)
		self.entry_albumTitle.place(x=200, y=110)

		self.entry_genre = ttk.Entry(self)
		self.entry_genre.place(x=200, y=140)

		self.entry_rating = ttk.Entry(self)
		self.entry_rating.place(x=200, y=170)

		btn_cancel = ttk.Button(self, text='Cancel', command=self.destroy)
		btn_cancel.place(x=300, y=210)

		self.btn_add = ttk.Button(self, text='ADD')
		self.btn_add.place(x=220, y=210)
		self.btn_add.bind('<Button-1>', lambda event: self.validate())

		self.grab_set()
		self.focus_set()

	def validate(self):
		artist = self.entry_artist.get()
		label = self.entry_label.get()
		album = self.entry_albumTitle.get()
		genre = self.entry_genre.get()
		rating = self.entry_rating.get()

		if any([len(string) == 0 for string in [artist, label, album, genre, rating]]):
			messagebox.showinfo("ERROR", "Fill in all the fields!")
		else:
			self.add_new_record()

	def add_new_record(self):
		self.view.records(self.entry_artist.get(),  # получение текста из поля
						  self.entry_label.get(),
						  self.entry_albumTitle.get(),
						  self.entry_genre.get(),
						  self.entry_rating.get())

		self.destroy()
		self.update()

class Update(Child):
	def __init__(self):
		super().__init__()
		self.init_edit()
		self.view = app
		self.db = DB()
		self.default_data()

	def init_edit(self):
		self.title('Edit')
		btn_edit = ttk.Button(self, text='Edit')
		btn_edit.place(x=220, y=210)
		btn_edit.bind('<Button-1>', lambda event: self.validate())
		self.btn_add.destroy()

	def validate(self):
		artist = self.entry_artist.get()
		label = self.entry_label.get()
		album = self.entry_albumTitle.get()
		genre = self.entry_genre.get()
		rating = self.entry_rating.get()

		if any([len(string) == 0 for string in [artist, label, album, genre, rating]]):
			messagebox.showinfo("Error", "Fill in all the fields!")
		else:
			self.update_records()

	def update_records(self):

		self.view.update_record(self.entry_artist.get(),
								self.entry_label.get(),
								self.entry_albumTitle.get(),
								self.entry_genre.get(),
								self.entry_rating.get())
		self.destroy()
		self.update()

	def default_data(self):
		self.db.c.execute('''SELECT * FROM release WHERE ID =?''',
						  (self.view.tree.set(self.view.tree.selection()[0], '#1'),))

		row = self.db.c.fetchone()  # возвращает одну строку данных

		artist = self.db.displayArtist('artist_id', row[2], 1)
		album = self.db.displayAlbumTitle('album_id', row[1], 1)
		genre = self.db.displayGenre('genre_id', row[4], 1)

		self.entry_artist.insert(0, artist)
		self.entry_label.insert(0, row[3])
		self.entry_albumTitle.insert(0, album)
		self.entry_genre.insert(0, genre)
		self.entry_rating.insert(0, row[5])

class Search(tk.Toplevel):
	def __init__(self):
		super().__init__()
		self.init_search()
		self.view = app

	def init_search(self):
		self.title('SEARCH')
		self.geometry('300x150+400+300')
		self.resizable(False, False)

		label_search = tk.Label(self, text="SERCH BY FIELD")
		label_search.place(x=30, y=20)

		label_search = tk.Label(self, text="FIELD")
		label_search.place(x=30, y=50)

		self.combobox_search = ttk.Combobox(self, values=[u'Artist', u'Label', u'AlbumTitle', u'Genre', u'Rating'])
		self.combobox_search.current(None)
		self.combobox_search.place(x=130, y=20, width=150)

		self.entry_search = ttk.Entry(self)
		self.entry_search.place(x=130, y=50, width=150)

		btn_search = ttk.Button(self, text='SEARCH')
		btn_search.place(x=125, y=85)

		btn_cancel = ttk.Button(self, text='Cancel', command=self.destroy)
		btn_cancel.place(x=205, y=85)

		btn_search.bind('<Button-1>', lambda event: self.validate())

	def validate(self):
		if len(self.entry_search.get()) == 0 or len(self.combobox_search.get()) == 0:
			messagebox.showinfo("Error", "Fill in all the fields!")
		else:
			self.view.search_records(self.combobox_search.get(), self.entry_search.get())
			self.destroy()

if __name__ == "__main__":
	root = tk.Tk()
	app = Main(root)
	app.pack()
	root.title("MUSIC")
	root.geometry("1400x450+100+100")
	root.resizable(False, False)
	root.mainloop()
