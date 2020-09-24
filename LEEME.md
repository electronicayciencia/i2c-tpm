Prácticas con TPM virtual
=========================

Instalación
-----------

### Software TPM 1.2 

Es un emulador para practicar. Es conforme a la especificación TPM 1.2, no 2.0.

https://sourceforge.net/projects/ibmswtpm/

Tiene tres directorios:
    /libtpm      
    /tpm         
    /tpm_proxy   

El que nos interesa es `tpm`. Libtpm no he conseguido compilarlo con la libería OpenSSL 1.1. En el foro de soporte te dicen que uses trousers: 
[hilo en el foro de sourceforge](https://sourceforge.net/p/ibmswtpm/discussion/1137021/thread/9c05f6703c/?limit=250).

Leemos el README del directorio TPM para compilarlo.

Una vez levantado escucha en un puerto TPC.


### Api TSS

La capa de software se llama TrouSerS. Tiene un demonio tscd que escucha en el puerto 30003 y se comunica con el TPM software.

Hay que bajar los paquetes TSS y tpm-tools. También están en la paquetería del sistema.


Primer arranque
---------------

### Inicialización del TPM en el arranque

Ejecutar servidor de TPM virtual de IBM

    TPM_PATH=. TPM_PORT=6543 TPM_DEBUG=0 ./tpm_server

Como no tengo las utilidades, porque no compilaron, no puedo ejecutar `tmpbios` y en su lugar debo inicializarlo a mano. 

Este paso lo haría la BIOS o UEFI antes de arrancar el sistema. Hasta entonces cualquier interacción devolverá el código 0x26 `TPM_INVALID_POSTINIT`.

Lanzar comando TPM_Init (97):

    tag:        00 C1         (TPM_TAG_RQU_COMMAND)
    paramSize:  00 00 00 0A
    ordinal:    00 00 00 97   (TPM_ORD_Init)


    echo -e '\x00\xC1\x00\x00\x00\x0A\x00\x00\x00\x97' | netcat localhost 6543

O también con

    echo -e '\x00\xC1\x00\x00\x00\x0A\x00\x00\x00\x97' > /dev/tcp/127.0.0.1/6543



Lanzar comando TPM_Startup (99), estado clear:

    tag:         00 C1         (TPM_TAG_RQU_COMMAND)
    paramSize:   00 00 00 0C
    ordinal:     00 00 00 99   (TPM_ORD_Startup)
    startupType: 00 01         (TPM_ST_CLEAR)


    echo -e '\x00\xC1\x00\x00\x00\x0C\x00\x00\x00\x99\x00\x01' | netcat localhost 6543


Ahora seguiría la carga del arranque y el Sistema Operativo. Lo cual incluye un driver para acceso al TPM llamado -en linux- TCSD (Trusted Core Services Daemon): 


### Inicialización del demonio TSCD

Ejecutar driver:

    export TCSD_USE_TCP_DEVICE=true
    export TCSD_TCP_DEVICE_PORT=6543
    export TCSD_TCP_DEVICE_HOSTNAME=127.0.0.1
    tcsd -e -f

El TPM está aún en modo **disabled**. Se pueden ejecutar todos los comandos que la especificación marca como *Avail Disabled*. Como por ejemplo GetVersion

Pedir la versión:

    $ export TSS_DEBUG_OFF=1 
    $ export TSS_TCSD_HOSTNAME=127.0.0.1
    $ export TSS_TCSD_PORT=30003

    $ tpm_version
    TPM 1.2 Version Info:
    Chip Version:        1.2.18.160
    Spec Level:          2
    Errata Revision:     3
    TPM Vendor ID:       IBM
    TPM Version:         01010000
    Manufacturer Info:   49424d00



### Habilitar TPM

Al hacer cualquier operación devuelve error TPM_Disabled (0x07).

La habilitamos por medio de presencia física. Usamos presencia por software. Para lo cual hay que habilitar el comando:

    $ tpm_setpresence --enable-cmd
    Tspi_TPM_SetStatus failed: 0x00002006 - layer=tcs, code=0006 (6), Not implemented
    Change to Command Enable Failed

Pero tscd lo deniega mientras el sistema esté arrancado: 

    Physical Presence command denied: Must be in single user mode.

Como el TPM es virtual, no podemos asegurar presencia por hardware. Habilitamos el comando directamente mandándolo al TPM sin pasar por el TSC.

Comando 0x4000000A (TSC_ORD_PhysicalPresence). Parámetro 0x0020h (TPM_PHYSICAL_PRESENCE_CMD_ENABLE).

    tag:               00 C1         (TPM_TAG_RQU_COMMAND)
    paramSize:         00 00 00 0C
    ordinal:           40 00 00 0A   (TSC_ORD_PhysicalPresence)
    physicalPresence:  00 20         (TPM_PHYSICAL_PRESENCE_CMD_ENABLE)


    echo -e '\x00\xC1\x00\x00\x00\x0C\x40\x00\x00\x0A\x00\x20' | netcat localhost 6543 | hd


De nuevo pero cambiando el parámetro a TPM_PHYSICAL_PRESENCE_PRESENT.

    tag:               00 C1         (TPM_TAG_RQU_COMMAND)
    paramSize:         00 00 00 0C
    ordinal:           40 00 00 0A   (TSC_ORD_PhysicalPresence)
    physicalPresence:  00 08         (TPM_PHYSICAL_PRESENCE_PRESENT)


    echo -e '\x00\xC1\x00\x00\x00\x0C\x40\x00\x00\x0A\x00\x08' | netcat localhost 6543 | hd


En el log, el TPM acepta la presencia física:

    TPM_Process_PhysicalPresence: Setting physicalPresence TRUE

Ahora podemos activarlo desde el TSC usando Presencia Física como autorización:

    $ tpm_setenable --force --enable --well-known

En los logs está habilitado, pero desactivado:

    $ tpm_setenable --status --well-known
    Tspi_TPM_GetStatus failed: 0x00000006 - layer=tpm, code=0006 (6), TPM is deactivated

Ya tenemos a nuestra disposición los comandos marcados como *Avail Deactivated*.



### Activar el TPM

Activar el TPM (requiere presencia física):

    $ tpm_setactive  --active

Se requiere reboot. Paramos `tpm_server` y `tcsd`. 

Volvemos a hacer la inicialización por *BIOS*. El log del TPM virtual debe indicar que no está disabled, pero tampoco está *owned*.

    TPM_State_Trace: disable 0 p_deactive 0 v_deactive 0 owned 0 state 2

Podríamos listar las PCRs con el comando `./list_pcrs` ([list_pcrs.c](pruebas/list_pcrs.c)):

    $ ./list_pcrs
    PCR List
    PCR00: 0000000000000000000000000000000000000000
    PCR01: 0000000000000000000000000000000000000000
    PCR02: 0000000000000000000000000000000000000000
    PCR03: 0000000000000000000000000000000000000000
    PCR04: 0000000000000000000000000000000000000000
    PCR05: 0000000000000000000000000000000000000000
    PCR06: 0000000000000000000000000000000000000000
    PCR07: 0000000000000000000000000000000000000000
    PCR08: 0000000000000000000000000000000000000000
    PCR09: 0000000000000000000000000000000000000000
    PCR10: 0000000000000000000000000000000000000000
    PCR11: 0000000000000000000000000000000000000000
    PCR12: 0000000000000000000000000000000000000000
    PCR13: 0000000000000000000000000000000000000000
    PCR14: 0000000000000000000000000000000000000000
    PCR15: 0000000000000000000000000000000000000000
    PCR16: 0000000000000000000000000000000000000000
    PCR17: ffffffffffffffffffffffffffffffffffffffff
    PCR18: ffffffffffffffffffffffffffffffffffffffff
    PCR19: ffffffffffffffffffffffffffffffffffffffff
    PCR20: ffffffffffffffffffffffffffffffffffffffff
    PCR21: ffffffffffffffffffffffffffffffffffffffff
    PCR22: ffffffffffffffffffffffffffffffffffffffff
    PCR23: 0000000000000000000000000000000000000000

Las PCRs tienen 20 bytes, la misma longitud que un SHA-1. Además, como es un hash de tipo *Merkle–Damgård* se puede extender por bloques.


### Crear Endorsement Key

Normalmente esta clave viene creada ya de fábrica. Pero no es el caso aquí:

    $ tpm_getpubek 
    Tspi_TPM_GetPubEndorsementKey failed: 0x00000023 - layer=tpm, code=0023 (35), No EK

Ejecutamos el comando `tpm_createek` para crearla. El ya debería devolver datos.

    $ tpm_getpubek 
    Public Endorsement Key:
      Version:   01010000
      Usage:     0x0002 (Legacy)
      Flags:     0x00000000 (!VOLATILE, !MIGRATABLE, !REDIRECTION)
      AuthUsage: 0x00 (Never)
      Algorithm:         0x00000020 (RSA)
      Encryption Scheme: 0x00000012 (RSAESOAEP_SHA1_MGF1)
      Signature Scheme:  0x00000010 (None)
      Key Size:          2048 bits
      Public Key:
        b22a1f6e d79d4bf8 b65c647e 1a286911 32d9d3a1 c2225fc1 a0b500d9 c4783cb9
        [....]
        b5ca46d2 5237c286 b18f9e40 e746fefe 44c00b31 c23da490 36c07e53 7616ce77


Esta clave sólo la ve y la usa el propio TPM. Por lo que no lleva contraseña. La siguiente clave la Storage Root Key (SRK) es más práctica. Para crearla debemos crear una contraseña de acceso al TPM, este proceso se llama *tomar posesión*.


### Tomar posesión

Tomar posesión del TPM (take ownership) consiste en crear la clave SRK y protegerla con una contraseña (en nuestro caso, todo ceros).

    $ tpm_takeownership --owner-well-known --srk-well-known

En el log del TPM virtual se indica que ya tiene dueño:

    TPM_State_Trace: disable 0 p_deactive 0 v_deactive 0 owned 1 state 2

La clave SRK tampoco sale del dispositivo y para usarla es necesario haberse autenticado con la debida contraseña.


Prácticas
---------


### Generar un número random

TPM_ORD_GetRandom 0x00000046

    tag:               00 C1         (TPM_TAG_RQU_COMMAND)
    paramSize:         00 00 00 0E
    ordinal:           00 00 00 46   (TPM_ORD_GetRandom)
    bytesRequested:    00 00 00 14   (20 bytes)


    echo -e '\x00\xC1\x00\x00\x00\x0E\x00\x00\x00\x46\x00\x00\x00\x14' | netcat localhost 6543 | hd


### Extender PCR

Ejecutar el programa [extend_pcr](pruebas/extend_pcr.c) indicando el número de PCR. Este programa extiende la PCR con un digest de 20 bytes a cero y devuelve el nuevo valor.


    $ ./extend_pcr 0
    PCR00: b80de5d138758541c5f05265ad144ab9fa86d1db

El valor que toma *b80de5d138758541c5f05265ad144ab9fa86d1db* corresponde al SHA1 del digest anterior (veinte ceros) concatenado con el nuevo valor (otros veinte ceros). Lo cual es fácil de comprobar:

    $ perl -e 'print "\x00"x40' | sha1sum
    b80de5d138758541c5f05265ad144ab9fa86d1db  -

Como estamos operando con la *locality* 0, sólo podemos modificar las PCRs de la 0 a la 16 y la 23:

    $ ./extend_pcr 17
    Tspi_TPM_PcrExtend: Locality is incorrect for attempted operation


### Guardar un secreto

La característica más distintiva de un TPM es poder guardar un secreto bajo una clave y ligado al estado actual del sistema.

Este es el texto claro:

    $ cat data/cleartext 
    Twas brillig, and the slithy toves
    Did gyre and gimble in the wabe;
    All mimsy were the borogoves,
    And the mome raths outgrabe.

Podría ser la clave de cifrado de una partición de disco.

Ahora extendemos la PCR 0 una vez y la PCR 1 dos veces. Simulando que el sistema está en un estado X desde el arranque.

    $ ./list_pcrs 
    
    PCR List
    PCR00: b80de5d138758541c5f05265ad144ab9fa86d1db
    PCR01: 850659b18eb6fb4ccdcb113ca4266eb945449466
    PCR02: 0000000000000000000000000000000000000000
    PCR03: 0000000000000000000000000000000000000000
    PCR04: 0000000000000000000000000000000000000000
    ...

Con el comando `tpm_sealdata` guardaremos la clave anterior condicionada a las PCRs 0, 1 y 2. 

    $ tpm_sealdata -i data/cleartext -o data/ciphertext.tss -p 0 -p 1 -p 2 -z

La z significa que la contraseña que hemos usado durante la *toma de posesión* ha sido todo ceros. En un sistema real tendríamos que proporcionar la contraseña de owner para desbloquear la SRK.

Este es el fichero encriptado:

    $ cat data/ciphertext.tss 
    -----BEGIN TSS-----
    -----TSS KEY-----
    AQEAAAARAAAABAEAAAABAAMAAQAAAAwAAAgAAAAAAgAAAAAAAAAAAAABAJsAYu7R
    iva8VJQHy1jS7+NGFeYApb3jyuJ87xpAEK/8Z+PngxJMyDMdtgfMJTXhTnkof5n5
    6zCyO+zPjTclDUJFmhr62AmQDEymnSJ0TwROg7efEG+oqLJSvCE2rexuUDcffoRy
    sz79LW3AeLkLLCOzE2oQxzcdy37/O5rFnmzaG0kWkYiPQcKhz1gb9csJ1n9IdU8k
    f2Wl1erYZMAkUDuSqFVf1YaoUhWR6QvRkdklHU/yConLJ0ISkRy6Y62twmdhPZql
    f3wEDdTQa31cX0ooSSYJyb1ls0leRRDkQAW377usXQRZ2Qecvv5ACImSlAIvvunp
    9s1dMLDZ0QjKGysAAAEAoBy2ZKdHjuSPACcVaiMhwpMA1wIepo2s0KQMaHgxxaDk
    MVOGfJ55tGPXLsb0ysGIoK/V58a8gXNkW85zWTsUVdQ86YYrieuhkpIKisbzGPC0
    uC+nNyVLDszLlyndEB6EEmAdVXAJdzAJXsehy0qGT5gvhrdnh3SwUM7mxK3uff0+
    Ku3YIb0Calkt50TA5sfdJFcAlePmQbdNDzHjKHEqBaZV4eGnP5gttuDzTYNLDNRc
    I22bWXct/1LK+6Be3NjU8eey7A6KcLBHA9rg+Ah/jRHmlJdpNM2aZHPWHdfj3AIV
    KY4uHZo4jpt4lG/DRvIEPM3wANUZVhG5wEDlNe7TOQ==
    -----ENC KEY-----
    Symmetric Key: AES-256-CBC
    AQEAAAAAACwAAgcArgAOY/acjhh3BnJjsKcq6n5QtOuuAA5j9pyOGHcGcmOwpyrq
    flC06wAAAQBhCZW7rSZa+RJOP1iEPYoqryK3sV+juqdm2upM7r27Dd2FpqgokFcJ
    PYoy8gLpOrsoTsN4ds4wu9TD7WY1Feda09u330s6yfqrwpyCh1xbTw65ZfRKlMJh
    tNPbecczNHEz+K3qq23k5jz5+hLhukQEM70lvOMraXa9M/2WtApvWpOGVVlPoxbQ
    +nkfqvbaKOPTAPij7ITDwjPlRLmpZ1oOA0vUTz45KiCf226l7pw/9wa1XJBx7OqL
    HhSW72KVFkHHRa8s/NqSm22wK7IMp77zjaoAt6xBYqSxBPQYJG6HI3vfPobqFUfE
    ovlFCm7lgqpMQfqvWP2x8ycDE4WcyFC5
    -----ENC DAT-----
    sDY11ZeNAGf+4mXrVLplTpnjFrNjiqpFYdJ1H6PJSkEL2g4fJNGlQuzmQoNhkEdO
    OoGi4A5vtKglywI+I/AaV2ZCN5AAi4Nggtnqj6OyxwP9s6vWh556aK6N0tcuufan
    /qbDd+KIYyc++B12GUDdFfj4pKeDcmnMxOfZHY0MfTM=
    -----END TSS-----



### Descifrar un secreto


Para desencriptarlo usamos el comando `tpm_unsealdata`.

    $ tpm_unsealdata -i data/ciphertext.tss -z 
    Twas brillig, and the slithy toves
    Did gyre and gimble in the wabe;
    All mimsy were the borogoves,
    And the mome raths outgrabe.

Pero el desencriptado sólo funcionará si las PCRs 0, 1 y 2 tienen el mismo valor que cuando se cifró. Si extendemos por ejemplo la PCR 2:

    $ ./extend_pcr 2
    PCR02: b80de5d138758541c5f05265ad144ab9fa86d1db
    $ ./list_pcrs 
    
    PCR List
    PCR00: b80de5d138758541c5f05265ad144ab9fa86d1db
    PCR01: 850659b18eb6fb4ccdcb113ca4266eb945449466
    PCR02: b80de5d138758541c5f05265ad144ab9fa86d1db
    PCR03: 0000000000000000000000000000000000000000
    PCR04: 0000000000000000000000000000000000000000

Ahora no funciona.

    $ tpm_unsealdata -i data/ciphertext.tss -z
    $ 

Las PCRs (salvo la 16 y la 23) no se pueden reinciar a cero. Por tanto la única forma de que vuelvan a tener el mismo valor que cuando se cifró la clave es reiniciar el sistema (apagar la TPM) reproducir los mismos pasos.

Inicializar TPM (equivalente a reiniciar el sistema cortando la alimentación):

    $ echo -e '\x00\xC1\x00\x00\x00\x0A\x00\x00\x00\x97' > /dev/tcp/127.0.0.1/6543
    $ echo -e '\x00\xC1\x00\x00\x00\x0C\x00\x00\x00\x99\x00\x01' > /dev/tcp/127.0.0.1/6543

Extender con ceros 1 vez la PCR 0 y dos veces la PCR 1

    $ ./extend_pcr 0
    PCR00: b80de5d138758541c5f05265ad144ab9fa86d1db
    $ ./extend_pcr 1
    PCR01: b80de5d138758541c5f05265ad144ab9fa86d1db
    $ ./extend_pcr 1
    PCR01: 850659b18eb6fb4ccdcb113ca4266eb945449466

Y ahora sí podemos acceder a la clave:

    $ tpm_unsealdata -i data/ciphertext.tss -z
    Twas brillig, and the slithy toves
    Did gyre and gimble in the wabe;
    All mimsy were the borogoves,
    And the mome raths outgrabe.





## Bibliografía

Emulation of TPM on Raspberry Pi - Marcus Sundberg & Erik Nilsson
https://www.eit.lth.se/sprapport.php?uid=848

A Hijacker's Guide to the LPC bus
https://online.tugraz.at/tug_online/voe_main2.getvolltext?pCurrPk=59565

TrouSerS FAQ
http://trousers.sourceforge.net/faq.html

System Design Manufacturing Recommendations for Atmel TPM Devices - Microchip
http://ww1.microchip.com/downloads/en/AppNotes/Atmel-8882-TPM-System-Design-Mftg-Recommendations-ApplicationNote.pdf

Linux TPM Encryption: Initializing and Using the TPM
https://resources.infosecinstitute.com/linux-tpm-encryption-initializing-and-using-the-tpm/

A Practical Guide to TPM 2.0
https://link.springer.com/book/10.1007/978-1-4302-6584-9


tpm2-software/tpm2-tss
https://github.com/tpm2-software/tpm2-tss