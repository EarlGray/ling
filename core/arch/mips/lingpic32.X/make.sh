#!/bin/bash

# how to build project from command line:
case "$(uname)" in
  Darwin) MPLABX_HOME=/Applications/microchip/mplabx/mplab_ide.app/Contents/Resources/mplab_ide ;;
  *)
    echo "Set \$MPLABX_HOME" >&2 ; exit 1 ;;
esac

export PATH=$MPLABX_HOME/bin:$PATH

make TYPE_IMAGE=DEBUG_RUN $@
