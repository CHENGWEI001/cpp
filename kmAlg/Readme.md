# note
* example:
    ```
        g1  g2
    b1  4   1
    b2  4   2

    from above , we want to match b1 and b2 with g1 and g2
    i = 0 , at b1, we match b1 and g1, then break
    i = 1 , at b2, we match b2 and g1, but found g1 already link with b1, so we try to rematch b1, but fail
        then we try to update cx and cy, idea is to find any other pair for usex[i] && !usey[j] for i.
        in above example , since (b2, g2) pair not use yet, so we update cx[1] = 2, purpose is to have b2
        get the chance to match with g2, also we update cy[1] = 2, purpose is to still keep original (b1, g1)
        and (b2, g2) can match
    ```