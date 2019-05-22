#!/usr/bin/env python
"""
Calculate relative branching fraction of jpsi->invi over jpsi->mumu
"""

__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) XIAO Suyu"
__created__ = "[2018-04-13 Fri 11:14]"

import math
import sys

logdir = sys.argv[1:]
print logdir

def error_mul(A, a, B, b):
    D = A * B
    d = D * math.sqrt( (a/A)**2 + (b/B)**2 )
    return D, d

def error_div(A, a, B, b):
    D = A / B
    d = D * math.sqrt( (a/A)**2 + (b/B)**2 )
    return D, d

def error_sub(A, a, B, b):
	D = A - B
	d = math.sqrt(a**2 + b**2)
	return D, d

def error_add(A, a, B, b):
	D = A + B
	d = math.sqrt(a**2 + b**2)
	return D, d

# for data 2009
if logdir in [['09']]:
    inv_down, e_inv_down = error_mul(40.60, 0.07, 0.994, 0.001)
    inv, e_inv = error_div(-4098.0, 2667.0, inv_down, e_inv_down)
    print "invi = %.2f +- %.2f" %(inv, e_inv)
    mumu, e_mumu = error_div(713652.0, 3497.0, 32.36, 0.03)
    print "mumu = %.2f +- %.2f" %(mumu, e_mumu)
    stat_invi = -4098.0 / 40.60 / 0.994
    stat_invi_err = 384.0 / 40.60 / 0.994
    stat_mumu = 713652.0 / 32.36
    stat_mumu_err = 693.0 / 32.36
    stat, stat_err = error_div(stat_invi, stat_invi_err, stat_mumu, stat_mumu_err)

    E, e = error_div(inv, e_inv, mumu, e_mumu)


# for data 2012
elif logdir in [['12']]:

    inv_down, e_inv_down = error_mul(39.25, 0.07, 0.998, 0.0004)
    inv, e_inv = error_div(-70776.0, 9233.0, inv_down, e_inv_down)
    print "invi = %.2f +- %.2f" %(inv, e_inv)
    mumu, e_mumu = error_div(2224671.0, 10901.0, 31.44, 0.03)
    print "mumu = %.2f +- %.2f" %(mumu, e_mumu)
    stat_invi = -70776.0 / 39.25 / 0.998
    stat_invi_err = 384.0 / 40.60 / 0.994
    stat_mumu = 2224671.0 / 31.44
    stat_mumu_err = 1275.0 / 31.44
    stat, stat_err = error_div(stat_invi, stat_invi_err, stat_mumu, stat_mumu_err)

    E, e = error_div(inv, e_inv, mumu, e_mumu)



    # inv_down, e_inv_down = error_mul(39.25, 0.07, 0.998, 0.0004)
    # c = 443620.0+13779.0*0.998
    # f = 396471.0*0.0047
    # aaa, bbb = error_sub(396471.0, f, c, 9725.0)
    # # c = 411966.0+13779.0*0.998
    # # f = 368711.0*0.0047
    # # aaa, bbb = error_sub(368711.0, f, c, 9725.0)
    # print "N_invi = %.2f +- %.2f" %(aaa, bbb)
    # inv, e_inv = error_div(aaa, bbb, inv_down, e_inv_down)
    # print "invi = %.2f +- %.2f" %(inv, e_inv)
    # g = 2224671.0*0.0049
    # print "N_mumu = %.2f +- %.2f" %(2224671.0, g)
    # mumu, e_mumu = error_div(2224671.0, g, 31.44, 0.03) 
    # print "mumu = %.2f +- %.2f" %(mumu, e_mumu)

    # E, e = error_div(inv, e_inv, mumu, e_mumu)
    # invi_1 = aaa/0.998/39.25
    # invi_2 = 683.0/0.998/39.25
    # mumu_1 = 2224671.0/31.44
    # mumu_2 = 1275.0/31.44
    # stat, stat_err = error_div(invi_1, invi_2, mumu_1, mumu_2)


else:
    print 'input error'

print "%f =? %f" %(E*10000, stat*10000)
print "B/B = (%f +- %f +- %f)*10^-4" %(E*10000, stat_err*10000,  e*10000)






# for combine
# aaa, bbb = error_add(-670.0, 2987.0, -60900.0, 9901.0)
# print "N_invi = %.2f +- %.2f" %(aaa, bbb)
# e_com = (40.48 + 39.25) / 2.0
# print "e_com = %.2f" %(e_com)
# trig_n1 = 4212.0+11911.0
# trig_n2 = 4237.0+11934.0
# trig_com = trig_n1 / trig_n2
# trig_err = math.sqrt(trig_com*(1-trig_com)/trig_n2)
# print 'trig_com = %.4f +- %f'  % (trig_com, trig_err)
# ccc, ddd = error_add(713652.0, 3497.0, 2224671.0, 10901.0)
# print "N_mumu = %.2f +- %.2f" %(ccc, ddd)
# e_mumu_com = (32.36 + 31.44) / 2.0
# print "e_mumu_com = %.2f" %(e_mumu_com)

# inv_down, e_inv_down = error_mul(e_com, 0.07, trig_com, trig_err)
# inv, e_inv = error_div(aaa, bbb, inv_down, e_inv_down)
# mumu, e_mumu = error_div(ccc, ddd, e_mumu_com, 0.03)
# E, e = error_div(inv, e_inv, mumu, e_mumu)

# invi_stat, invi_stat_err = error_add(-670.0, 406.0, -60900.0, 683.0)
# mumu_stat, mumu_stat_err = error_add(713652.0, 693.0, 2224671.0, 1275.0)
# stat, stat_err = error_div(invi_stat/inv_down, invi_stat_err/inv_down, mumu_stat/e_mumu_com, mumu_stat_err/e_mumu_com)



