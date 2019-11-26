import requests
from bs4 import BeautifulSoup
import csv

#モンスターデータを取得
def get_monster_data():
    for i in range(1,9):
        #url="https://kyokugen.info/dq5/mon"+str(i)+".html"
        url="https://kyokugen.info/dq5/man"+str(i)+".html"
        try:
            html = requests.get(url)
            html=html.content.decode('utf-8')

            soup=BeautifulSoup(html, 'html.parser')
            print(url)
            print(soup.h2)
            char_name=soup.h2.getText().split('\u3000')[1].split('：')[0]
        except:
            continue

        table=soup.find_all("table")

        status_table_id=0

        for i,table_text in enumerate(table):
            if "必要経験値" in str(table_text):
                status_table_id=i

#        with open(char_name+"_status.csv", "w", encoding='cp932', newline='') as file:
#            writer = csv.writer(file)
#            for row in table[status_table_id].find_all("tr"):
#                csvRow = []
#                for cell in row.findAll(['td', 'th']):
#                    csvRow.append(cell.text)
#                writer.writerow(csvRow)

        with open(char_name+"spell.csv", "w", encoding='cp932', newline='') as file:
            writer = csv.writer(file)
            for row in table[status_table_id-1].find_all("tr"):
                it = iter(row.findAll(['td', 'th']))
                for cell in it:
                    csvRow = []
                    csvRow.append(cell.text[2:])
                    csvRow.append(next(it).text)
                    writer.writerow(csvRow)
#武器　よろい　たて　かぶと　そうしょくひん　どうぐ
def get_item_data():
    pattern=[["武器","w"],["よろい","a"],["たて","s"],["かぶと","h"],["そうしょくひん","ac"],["どうぐ",""]]
    for name,prefix in pattern:
        url="https://kyokugen.info/dq5/dq5_ds_item"+prefix+"1.html"
        print(url)
        html = requests.get(url)
        html=html.content.decode('utf-8')
        soup=BeautifulSoup(html, 'html.parser')
        table=soup.find_all("table")

        target_table_id=0

        for i,table_text in enumerate(table):
            if "名前" in str(table_text):
                target_table_id=i
                print(i)
        print(table[target_table_id])
        
        with open(name+".csv", "w", encoding='cp932', newline='') as file:
            writer = csv.writer(file)
            for row in table[target_table_id].find_all("tr"):
                csvRow = []
                for cell in row.findAll(['td', 'th']):
                    csvRow.append(cell.text)
                writer.writerow(csvRow)
get_monster_data()
