```
// Pulse response RC-network

delta_t = 0.005  t_end = 1.3  width_t = 6  precision_t = 3

1 PLS       off=0.0 on=1.0 t_on=0.1 t_off=0.5
2 ATT 1,-3  RC=0.1    // RC time constant = 0.1 sec
3 INT 2     out_t0=0.0

4 LOG 1,3 w=4 p=3  w=4 p=3
```
