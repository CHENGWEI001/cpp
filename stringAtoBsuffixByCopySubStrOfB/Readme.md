    给２个string　A　B，　求最少操作数能让A变成B的suffix。操作指从B里拿一个string的copy放到后面，保证可以完成。　比如　A：　“ａｂｃｄ”　B：　“ｄｂｃｆｄａ”　答案就是２，　B最后变成“ｄｂｃｆｄａｂｃｄ”。　解释：　“ａ”可以重用。　copy字串“ｂｃ”，　然后copy字串“ｄ”。　完成。　copy　２　次。
    用dp做的。
    下面有人的回复: 
    我的想法是先把可以重复用的去掉，比如dbcfda最后一个a和abcd里面的a相同，所以变成 dbcfda 和 bcd进行match，也就是求dbcfda最少的copy次数能形成bcd的dp思想。

    some comment below , but don't trust too much
    我看这个题目的意思就是copy 然后放在B的后面
