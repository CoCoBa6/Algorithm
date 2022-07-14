from itertools import combinations
def solution(orders, course):
    answer = []
    menus = set(list(('').join(orders)))
    maxCourseLen = max(list(map(lambda o:len(o), orders)))
    print(maxCourseLen)
    allCoursesByLen = {}
    for l in course:
        if l > maxCourseLen:
            break
        allCoursesByLen[l] = list(combinations(menus, l
    ordersSet = list(map(set, orders))
    print(ordersSet)
    
    
    for l in course:
        if l > maxCourseLen:
            break
        courseDict = {}
        for o in ordersSet:
            for c in allCoursesByLen[l]:
                if len(c) > len(o):
                    break
                if len(c) <= len(o) and set(c).issubset(o):
                    if c in courseDict:
                        courseDict[c] = courseDict[c] + 1
                    else:
                        courseDict[c] = 1
        sortedCourseDict = sorted(courseDict.items(), key = lambda item: item[1], reverse = True)
        countList = list(courseDict.values())
        if len(countList) > 0:
            maxCount = max(countList)
            if maxCount >= 2:
                answer += sorted(list(map(lambda c:('').join(sorted(c[0])), list(filter(lambda elem:elem[1] == maxCount, courseDict.items())))))
    
    return sorted(answer)