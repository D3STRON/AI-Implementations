import random
Days = 6
Classes = 4
Periods = 4
F = 0
mutation_rate = 0.01
tt = [ [ [ 'n/a' for clas in range(Classes) ] for period in range(Periods) ] for day in range(Days) ] 
subs = ['eng','mr','eco','oc','sp','bk']
weekDays = ['MonDays','TuesDays','WednesDays','ThursDays','FriDays','SaturDays']
lec_per_sub_per_clas = (Days*Periods)/len(subs)
#stores the number of lectures per subject per class will have
classsubfreq = [[ lec_per_sub_per_clas for sub in range(len(subs)) ] for clas in range(Classes) ]

def sublockerIni(k):
    if k ==2:
        #sets the number of occurance of a subject in a perticular day to zero initially
        return 0
    else:
        #sets all conflicts of lectures to none initially
        return [ -1 for l in range(Classes) ]

#this data structure tracks the subjects occurance in a day,
#parallel occurances during a period in multiple classes,
#orrurance in same class in two different periods per day basis
#this is for the fitness calculation
sublocker = [ [ [ sublockerIni(k) for k in range(3) ] for day in range(Days) ] for sub in range(len(subs)) ]
F = 0

def fitness(ttn, nsublocker):
    f = 0
    for day in range(Days):
        d=[]
        for period in range(Periods):
            for clas in range(Classes):
                subject = ttn[day][period][clas]
                #the logic around the arraylist d ensures no subject lecture is placed in the begning and in the end of the day(was a requirement of client)
                if period == 0:
                    d.append(ttn[day][period][clas])
                elif period == Periods-1 and (ttn[day][period][clas] in d):
                    f-=1
                elif ttn[day][period][clas] in d:
                    d.remove(ttn[day][period][clas])
                #if there are same lectures in two class in the same period reduce fitness
                if nsublocker[subject][day][0][period] >0:
                    f-=1
                #if there are same lectures in same class consecutively reduce fitness    
                if nsublocker[subject][day][1][clas] >0:
                    f-=1
                #if in a day a number of lectures of a subjects is equalt to or greater than the number of periods reduce fitness
                if nsublocker[subject][day][2]>=Periods:
                    f-=1
    return f

def place(ptt,i,j,k,nsublocker):
    subject = ptt[i][j][k]
    nsublocker[subject][i][0][j] +=1
    nsublocker[subject][i][1][k] +=1
    nsublocker[subject][i][2]+=1
    return ptt[i][j][k]

def generateChild(ptt,F):
    nsublocker = [ [ [ sublockerIni(k) for k in range(3) ] for day in range(Days) ] for sub in range(len(subs)) ]
    ttn =[ [ [ place(ptt,day,period,clas,nsublocker) for clas in range(Classes) ] for period in range(Periods) ] for day in range(Days) ]
    for i in range(Days):
        for j in range(Periods):
            for k in range(Classes):
                subjectA = ttn[i][j][k]
                ni = random.randint(0,Days-1)
                nj = random.randint(0,Periods-1)
                nk = random.randint(0,Classes-1)
                if random.uniform(0, 1)<mutation_rate:
                    subjectB = ttn[ni][nj][nk]
                    ttn[ni][nj][nk] = subjectA
                    ttn[i][j][k] = subjectB
                    nsublocker[subjectA][ni][0][nj] += 1
                    nsublocker[subjectA][ni][1][nk] += 1
                    nsublocker[subjectA][ni][2]+=1
                    nsublocker[subjectB][i][0][j] += 1
                    nsublocker[subjectB][i][1][k] += 1
                    nsublocker[subjectB][i][2]+=1
                    nsublocker[subjectB][ni][0][nj] -= 1
                    nsublocker[subjectB][ni][1][nk] -= 1
                    nsublocker[subjectB][ni][2]-=1
                    nsublocker[subjectA][i][0][j] -= 1
                    nsublocker[subjectA][i][1][k] -= 1
                    nsublocker[subjectA][i][2]-=1
    f =fitness(ttn,nsublocker)
    return [ttn,f]
                
#Generating a initial parent
for day in range(Days):
    for period in range(Periods):
        for clas in range(Classes):
            random_sub = random.randint(0,len(subs)-1)
            while classsubfreq[period][random_sub]==0:
                random_sub = random.randint(0,len(subs)-1)
            sublocker[random_sub][day][0][period] +=1
            sublocker[random_sub][day][1][clas] +=1
            sublocker[random_sub][day][2]+=1
            tt[day][period][clas]=random_sub
            #checks the number of lectures of a subject allotted to a class is within said limits
            classsubfreq[period][random_sub]-=1
F = fitness(tt,sublocker)
while F<0:
    result = generateChild(tt,F)
    if result[1]>F:
        print("conflicts"+str(result[1]))
        F = result[1]
        tt = result[0]        
for day in range(Days):
    print(weekDays[day])
    for period in range(Periods):
        for clas in range(Classes):
            print(subs[tt[day][period][clas]]+"\t", end =" ")
        print(""),
    print("\n\n")    
