class LogEntry:
    def __init__(self):
        self.cntPerson = 0
        self.cntDogs = 0
        self.time = ""
        self.date = ""

# Function definition is here
def readLog(filePath):
    f = open(filePath, "r")
    out = []
    for x in f:
        logRow = LogEntry()
        rowArr = x.split(',')
        logRow.date = rowArr[0]
        logRow.time = rowArr[1]
        cntPerson = 0
        cntDogs = 0
        for el in rowArr:
            if el == 'person':
                cntPerson += 1
            elif el == 'dog':
                cntDogs += 1
        logRow.cntPerson = cntPerson
        logRow.cntDogs = cntDogs
        out.append(logRow)
    f.close()
    return out
