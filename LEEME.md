Interfaz i2c para TPM de Microchip
==================================



## Practicar con TPM Virtual de IBM

### Instalación


### Inicialización por BIOS:

Ejecutar servidor de TPM virtual de IBM

    TPM_PATH=. TPM_PORT=6543 TPM_DEBUG=0 ./tpm_server

Las utilidades no compilan con libssl 1.1.0. [hilo en el foro de sourceforge](https://sourceforge.net/p/ibmswtpm/discussion/1137021/thread/9c05f6703c/?limit=250).
Por tanto no puedo ejecutar `tmpbios` y en su lugar debo inicializarlo a mano. 

Este paso lo haría la BIOS o UEFI antes de arrancar el sistema. Hasta entonces cualquier interacción devolverá el código 0x26 `TPM_INVALID_POSTINIT`.

Lanzar comando TPM_Init (97):

    tag:        00 C1         (TPM_TAG_RQU_COMMAND)
    paramSize:  00 00 00 0A
    ordinal:    00 00 00 97   (TPM_ORD_Init)


    echo -e '\x00\xC1\x00\x00\x00\x0A\x00\x00\x00\x97' | netcat localhost 6543


Lanzar comando TPM_Startup (99), estado clear:

    tag:         00 C1         (TPM_TAG_RQU_COMMAND)
    paramSize:   00 00 00 0C
    ordinal:     00 00 00 99   (TPM_ORD_Startup)
    startupType: 00 01         (TPM_ST_CLEAR)


    echo -e '\x00\xC1\x00\x00\x00\x0C\x00\x00\x00\x99\x00\x01' | netcat localhost 6543


Ahora seguiría la carga del arranque y el Sistema Operativo. Lo cual incluye un driver para acceso al TPM llamado -en linux- TCSD (Trusted Core Services Daemon): 

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

    tpm_setpresence --enable-cmd
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

    tpm_setenable --force --enable --well-known

En los logs está habilitado, pero desactivado:

    $ tpm_setenable --status --well-known
    Tspi_TPM_GetStatus failed: 0x00000006 - layer=tpm, code=0006 (6), TPM is deactivated

Ya tenemos a nuestra disposición los comandos marcados como *Avail Deactivated*.



### Activar el TPM

Activar el TPM (requiere presencia física):

    tpm_setactive  --active

Se requiere reboot. Paramos `tpm_server` y `tcsd`. 

Volvemos a hacer la inicialización por *BIOS*. El log del TPM virtual debe indicar que no está disabled, pero tampoco está *owned*.

    TPM_State_Trace: disable 0 p_deactive 0 v_deactive 0 owned 0 state 2

Podríamos listar las PCRs con el comando `./listpcrs`

    $ ./listpcrs
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

    tpm_takeownership --owner-well-known --srk-well-known

En el log del TPM virtual se indica que ya tiene dueño:

    TPM_State_Trace: disable 0 p_deactive 0 v_deactive 0 owned 1 state 2

La clave SRK tampoco sale del dispositivo y para usarla es necesario haberse autenticado con la debida contraseña.












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



tpm2-software/tpm2-tss
https://github.com/tpm2-software/tpm2-tss