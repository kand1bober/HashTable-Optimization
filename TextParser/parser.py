import re

#-----------------------------------------------
def Parser(input_file, output_file):
    # Читаем текст из исходного файла
    with open(input_file, 'r', encoding='utf-8') as f:
        text = f.read()
    
    # Удаляем все небуквенные символы, оставляем только буквы и пробелы
    cleaned_text = re.sub(r'[^a-zA-Zа-яА-ЯёЁ\s]', '', text)
    
    # Разбиваем текст на слова (удаляем пустые строки)
    words = [word for word in cleaned_text.split() if word]
    
    # Записываем каждое слово на новой строке в выходной файл
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write('\n'.join(words) + '\n')

    ('\n')
#-----------------------------------------------


input_file = '../resources/Lotr_orig.txt'  
output_file = '../resources/Lotr_parsed.txt' 
Parser(input_file, output_file)
