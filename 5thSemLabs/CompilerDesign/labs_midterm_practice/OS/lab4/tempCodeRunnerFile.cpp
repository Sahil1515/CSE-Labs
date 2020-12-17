mkdir("newdir",0666);
    if(link(path,"agar")==0)
    perror("link");
    symlink(path,"Sahil");