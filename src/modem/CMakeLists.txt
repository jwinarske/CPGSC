
set(sources 
    m_uncfig.c
    m_echo.c
    m_ismsg.c
    m_prsmsg.c
    m_getstr.c
    m_cmdstr.c
    m_gocmd.c
    m_hup.c
    m_whoru.c
    m_wt4dcd.c
    m_dial.c
    m_reset.c
    m_cmd.c
    m_cmd_ok.c
    m_answer.c
    m_codes.c
    m_config.c
    m_redial.c
    m_procfg.c
    m_wrndcd.c
)

include_directories(${SIO_INC_DIR})

add_library(modem STATIC ${sources})
