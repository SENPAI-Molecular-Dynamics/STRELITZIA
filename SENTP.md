# SENTP: Senpai Transfer Protocol
```
SENTP 1.0
CONTROL

INIT / EXIT / HALT / CONT / PING

SENTP END
```

```
SENTP 1.0
BINARY
DESCRIPTOR
LENGTH

%DATA%

SENTP END
```

```
SENTP 1.0
ERROR

ERRNO
ERRDESC

SENTP END
```

## LENGTH:
Length of the raw %DATA% section

## DESCRIPTOR:
The type of data being transmitted
- `UNIVERSE`
- `RESULTS`
- `CONFIG`

## ERRNO:
Identifying error code

## ERRDESC:
Error string

