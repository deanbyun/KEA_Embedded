savedcmd_/home/test/project/kernel/kernel-study/study-local-raspi/modules/kobject/kobject-example.mod := printf '%s\n'   kobject-example.o | awk '!x[$$0]++ { print("/home/test/project/kernel/kernel-study/study-local-raspi/modules/kobject/"$$0) }' > /home/test/project/kernel/kernel-study/study-local-raspi/modules/kobject/kobject-example.mod