from os import getcwd


class PATH:
    CWD = getcwd()

    CONFIG = CWD + "/config/"
    SETTINGS = CONFIG + "settings.json"

    BIN = CWD + "/bin/"
    BIN_local = "bin/"


BINARIES_LINUX = (
    PATH.BIN + "binary"
)
BINARIES_WINDOWS = (
    PATH.BIN + "binary.exe"
)
