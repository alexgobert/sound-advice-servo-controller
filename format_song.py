def format():
    filename = input('Enter filename: ')

    newLines = ''
    with open(filename, 'r') as file:
        newLines += '{\n'
        for line in file.readlines():
            line = line.split(' ')
            line = f'{{{line[0]}, \"{line[1].strip()}\"}},'

            newLines += line + '\n'
        newLines += '}'

    newName = 'formatted_'+ filename
    with open(newName, 'w') as file:
        file.write(newLines)

if __name__ == '__main__':
    format()