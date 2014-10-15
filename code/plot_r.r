table = read.table('jerk_dynamic.txt', sep=',', comment.char=';')
plot(seq(0,0.04,by=0.0001), dnorm(seq(0,0.04,by=0.0001),mean=mean(table$V3),sd=sd(table$V3)),type='l')

 table = read.table('jerk_nondynamic.txt', sep=',', comment.char=';')
 plot(seq(-2,1,by=0.001), dnorm(seq(-2,1,by=0.001),mean=mean(table$V3),sd=sd(table$V3)),type='l')
 
  table = read.table('naive_nondynamic.txt', sep=',', comment.char=';')
 plot(seq(-0.1,0.1,by=0.0001), dnorm(seq(-0.1,0.1,by=0.0001),mean=mean(table$V3),sd=sd(table$V3)),type='l')
 
 table = read.table('naive_dynamic.txt', sep=',', comment.char=';')
plot(seq(0.02,0.03,by=0.0001), dnorm(seq(0.02,0.03,by=0.0001),mean=mean(table$V3),sd=sd(table$V3)),type='l')
