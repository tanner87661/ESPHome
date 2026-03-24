import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.const import CONF_ID
CONF_HOST = "host"
CONF_PORT = "port"

AUTO_LOAD = ["network"]

loconet_tcp_ns = cg.esphome_ns.namespace("loconet_tcp")
LocoNetTCP = loconet_tcp_ns.class_("LocoNetTCP", cg.Component)

CONF_ON_RECEIVE = "on_receive"
CONF_ON_SENT_OK = "on_sent_ok"

# Triggers
ReceiveTrigger = loconet_tcp_ns.class_("ReceiveTrigger", automation.Trigger.template(cg.std_string))
SentOkTrigger = loconet_tcp_ns.class_("SentOkTrigger", automation.Trigger.template(cg.std_string))

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(LocoNetTCP),
    cv.Required(CONF_HOST): cv.string,
    cv.Required(CONF_PORT): cv.port,
    cv.Optional(CONF_ON_RECEIVE): automation.validate_automation({
        cv.GenerateID(): cv.declare_id(ReceiveTrigger),
    }),
    cv.Optional(CONF_ON_SENT_OK): automation.validate_automation({
        cv.GenerateID(): cv.declare_id(SentOkTrigger),
    }),
}).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_HOST], config[CONF_PORT])
    await cg.register_component(var, config)

    if CONF_ON_RECEIVE in config:
        for conf in config[CONF_ON_RECEIVE]:
            trigger = cg.new_Pvariable(conf[CONF_ID], var)
            await automation.build_automation(trigger, [(cg.std_string, "x")], conf)

    if CONF_ON_SENT_OK in config:
        for conf in config[CONF_ON_SENT_OK]:
            trigger = cg.new_Pvariable(conf[CONF_ID], var)
            await automation.build_automation(trigger, [(cg.std_string, "x")], conf)
