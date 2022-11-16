from typing import List

def format():
    filename = input('Enter filename: ')

    newLines = ''
    with open(filename, 'r') as file:
        # newLines += format_map(file.readlines(), newLines)
        newLines += format_array(file.readlines(), newLines)
        # newLines += format_progmem_array(file.readlines(), newLines)

    newName = 'formatted_'+ filename
    with open(newName, 'w') as file:
        file.write(newLines)

def format_progmem_array(file_list: List[str], newLines: str):
    for idx, line in enumerate(file_list):
        line = line.rstrip('\n').split(' ')
        line.pop(0)
        
        for note_idx, elem in enumerate(line):
            newLine = f'const String jingleBellBeat{idx}_{note_idx}[] = {{'
            
            elem = elem.rstrip('\n')
            newLine += f'"{elem}", '

            newLine = newLine.rstrip(', ')
            newLine += '};\n'

            newLines += newLine
    
    newLines += ';'
    return newLines

def format_array(file_list: List[str], newLines: str):
    newLines += '{\n'
    for line in file_list:
        line = line.rstrip('\n').split(' ')
        line.pop(0)

        newLine = f'{{'
        for elem in line:
            elem = elem.rstrip('\n')
            newLine += f'"{elem}", '

        newLine = newLine.rstrip(', ')
        newLine += '},\n'

        newLines += newLine

    newLines += '};'
    return newLines

def format_map(file_list: List[str], newLines: str):
    newLines += '{\n'
    for line in file_list:
        line = line.rstrip('\n').split(' ')
        newLine = f'{{{line.pop(0)}, {{'
        
        for elem in line:
            elem = elem.rstrip('\n')
            newLine += f'"{elem}", '

        newLine = newLine.rstrip(', ')
        newLine += '}},\n'

        newLines += newLine

    newLines += '};'
    return newLines

if __name__ == '__main__':
    format()