# MVAS-CLI

----

# What is mvas-cli

> MVAS-CLI is a simple command line tool to handle MVAS on Linux kernel. With
this tool, it is possible to do a lot of basic operations by command line. 

----
# Commands

> Here you can find a list of all available command lines.

----
## List VAS and Segments

> If you want to list all VAS and segments, just type:

```
mvas -la
mvas --list
mvas -l
```

* l: list all by default
* a: all

> List only segments:

```
mvas -ls
```

> List only VAS:

```
mvas -lv
```

----
## Remove VAS and segment

> To remove a VAS:

```
mvas -r -v [VAS id number]
mvas --remove --vas [VAS id number]
```

* -r: Remove
* -v: Expect integer number for (VAS Id)

> Remove segment:

```
mvas -r -s [VAS id number]
mvas --remove --segment [VAS id number]
```

* -s: Expect integer number for (Segment id)

----
## Create VAS or Segment

> Create VAS:

```
mvas -c -n VASNAME0 -m 777
mvas --create --name VASNAME1 -mode 777
```

* -c: Create
* -n: VAS name
* -m: VAS mode

```
mvas -c -n SEGMENT0 -m 777 --start 0xC0DE000 --size 0x1000
mvas --create --name SEGMENT1 --mode 777 --start 0xC0DE000 --size 0x1000
```

* start: Start address for segment
* size: Size for segment
