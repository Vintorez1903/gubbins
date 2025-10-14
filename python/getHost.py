import subprocess
import re

def getHosts():
    print("finding hosts via ARP scan")
    hostList = subprocess.check_output(["arp-scan", "--localnet"]).decode('utf-8')
    commandResultArr = hostList.splitlines()
    hostArr = []
    counter = 0
    for line in commandResultArr:
        if (counter > 1 and counter < len(commandResultArr)-3):
            entryArray = line.split('\t')	
            hostArr.append(entryArray[0])
        counter+=1

    return hostArr

def getHostInfo(fileName):
    print("beginning service version detection")

    hostInfo = subprocess.check_output(["nmap","-sV","-iL",fileName]).decode('utf8')
    entries = re.split(r'Nmap scan report',hostInfo)


    activeHosts = []
    for i in entries:
        if 'All 1000 scanned ports on' not in i:
            activeHosts.append(i)
    return activeHosts

def writeOutput(inputArray,fileName):
    print("writing to file")
    with open(fileName, "w") as file:
        for i in inputArray:
            file.write(i+"\n")

def main():
    hosts = getHosts()

    openHosts = (hosts)
    writeOutput(openHosts,"hosts.txt")
    hostInfo = getHostInfo("hosts.txt")
    writeOutput(hostInfo,"hostInfo.txt")
    print("output can be viewed in hostInfo.txt")

main()
