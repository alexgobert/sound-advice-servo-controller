def format():
    filename = input('Enter filename: ')

    newLines = ''
    with open(filename, 'r') as file:
        newLines += '{\n'
        for line in file.readlines():
            line = line.rstrip('\n').split(' ')
            # newLine = f'{{{line.pop(0)}, std::vector<String> vect {{'
            newLine = f'{{{line.pop(0)}, {{'
            
            for elem in line:
                elem = elem.rstrip('\n')
                newLine += f'"{elem}", '

            newLine = newLine.rstrip(', ')
            newLine += '}},\n'

            newLines += newLine

        newLines += '};'

    newName = 'formatted_'+ filename
    with open(newName, 'w') as file:
        file.write(newLines)

if __name__ == '__main__':
    format()