from bs4 import BeautifulSoup
from database import DB

db = DB()


def get_site_data():
  with open("C:\\Users\\Марина\\Desktop\\Univers\\3 semestr\\YaP\\CourseWork\\AllMusic.html", encoding='utf-8') as file:
    src = file.read()

  soup = BeautifulSoup(src, "html.parser")

  table = soup.find('tbody')
  lines = table.findAll('tr')

  data = []

  for row in lines:
    if row:
      # print(row, '\n\n')
      artist = row.find('td', class_='artist')
      artist = artist.text.strip() if artist else ''

      label = row.find('td', class_='label')
      label = label.text.strip() if label else ''

      albumTitle = row.find('td', class_='album')
      albumTitle = albumTitle.text.strip() if albumTitle else ''

      genre = row.find('td', class_='genre')
      genre = genre.text.strip() if genre else ''

      try:
        rating = row.find('td', class_='rating').find('span')
        rating = rating.get('class')[1][-1] if rating.get('class') and rating.get('class')[1][-1] != '-' else '0'
      # print(rating)
      except:
        continue

      # print(f'{artist}\t{albumTitle}')

      data.append([artist, label, albumTitle, genre, rating])

  return data


def populate():
  data = get_site_data()
  # print(data)
  db.insert_records(data)


if __name__ == '__main__':
  populate()
