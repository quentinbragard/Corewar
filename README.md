<img src="https://cdn.rawgit.com/emilwallner/Corewar/master/images/corewarlogo.svg" width="100%">

---

**Project score : [124 / 100]**

**Core War was inspired by a malicious virus written in the 80’s.** To deal with the self-replicating virus, a white hat hacker invented Reaper. It was a virus designed to spread and eliminate the malware. He fought fire with fire.

Let’s focus on the high-level game dynamics: 

- **The game board**, the memory of our virtual computer. It’s represented in a 64 X 64 grid of bytes.
- **The players**, small programs represented in different colors. The white parts have blank memory.
- **Cursors**, the moving parts with inverted color. They read from the game board. 

## Installation and usage

```
git clone https://github.com/barthelemyleveque/corewar && cd corewar && make
```

First we need to translate the players (also called Champions) written in assembly language to bytecode.
For example, let's convert this champion : ```example/bee_gees.s```

![bee_gees_s](https://i.ibb.co/XZMvJB2/Screen-Shot-2019-10-28-at-1-37-48-PM.png)

```./asm examples/bee_gees.s```

Running this command, will create a new file : ```bee_gees.cor``` written in bytecode, that will be interpreted by the Virtual Machine :

```hexdump examples/bee_gees_.cor```

![bee_gees_cor](https://i.ibb.co/wJhsD7c/Screen-Shot-2019-10-28-at-1-40-48-PM.png)

## The Virtual Machine 

**Usage:**
```
Usage : ./corewar player1.cor player2.cor
Available options :
    -n      [-n player_number player.cor]
  -dump     [-dump cycle], stops the game
 -viewer    [-viewer], shows graphic mode
 ```
 
 Here is what the battle for the memory looks like with 4 champions :
 
 ```./corewar -viewer Octobre_Rouge_V4.2.cor Gagnant.cor championships/2017/tbillard/Douceur_power.cor examples/helltrain.cor ```

 ![gif](https://i.ibb.co/88qkGS0/gid.gif) 
 
 
