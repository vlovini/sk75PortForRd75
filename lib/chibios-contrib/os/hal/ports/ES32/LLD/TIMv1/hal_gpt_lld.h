/*
    Copyright (C) 2020 Yaotian Feng

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    hal_gpt_lld.h
 * @brief   PLATFORM GPT subsystem low level driver header.
 *
 * @addtogroup GPT
 * @{
 */

#ifndef HAL_GPT_LLD_H
#define HAL_GPT_LLD_H

#if (HAL_USE_GPT == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    PLATFORM configuration options
 * @{
 */
/**
 * @brief   GPTD1 driver enable switch.
 * @details If set to @p TRUE the support for GPTD1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(ES32_GPT_USE_BFTM0) || defined(__DOXYGEN__)
    #define ES32_GPT_USE_BFTM0               FALSE
#endif

#if !defined(ES32_GPT_USE_BFTM1) || defined(__DOXYGEN__)
    #define ES32_GPT_USE_BFTM1               FALSE
#endif

/**
 * @brief   GPTD1 interrupt priority level setting.
 */
#if !defined(ES32_GPT_BFTM0_IRQ_PRIORITY) || defined(__DOXYGEN__)
    #define ES32_GPT_BFTM0_IRQ_PRIORITY         7
#endif

#if !defined(ES32_GPT_BFTM1_IRQ_PRIORITY) || defined(__DOXYGEN__)
    #define ES32_GPT_BFTM1_IRQ_PRIORITY         7
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   GPT frequency type.
 */
typedef uint32_t gptfreq_t;

/**
 * @brief   GPT counter type.
 */
typedef uint16_t gptcnt_t;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct
{
    /**
     * @brief   Timer clock in Hz.
     * @note    The low level can use assertions in order to catch invalid
     *          frequency specifications.
     */
    gptfreq_t                 frequency;
    /**
     * @brief   Timer callback pointer.
     * @note    This callback is invoked on GPT counter events.
     */
    gptcallback_t             callback;
    /* End of the mandatory fields.*/
} GPTConfig;

/**
 * @brief   Structure representing a GPT driver.
 */
struct GPTDriver
{
    /**
     * @brief Driver state.
     */
    gptstate_t                state;
    /**
     * @brief Current configuration data.
     */
    const GPTConfig           *config;
#if defined(GPT_DRIVER_EXT_FIELDS)
    GPT_DRIVER_EXT_FIELDS
#endif
    /* End of the mandatory fields.*/
    BFTM_TypeDef *BFTM;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Changes the interval of GPT peripheral.
 * @details This function changes the interval of a running GPT unit.
 * @pre     The GPT unit must have been activated using @p gptStart().
 * @pre     The GPT unit must have been running in continuous mode using
 *          @p gptStartContinuous().
 * @post    The GPT unit interval is changed to the new value.
 * @note    The function has effect at the next cycle start.
 *
 * @param[in] gptp      pointer to a @p GPTDriver object
 * @param[in] interval  new cycle time in timer ticks
 * @notapi
 */
#define gpt_lld_change_interval(gptp, interval) \
    ((gptp)->BFTM->CMP = (ES32_CK_AHB_FREQUENCY / (gptp)->config->frequency) * (interval))

/**
 * @brief   Returns the interval of GPT peripheral.
 * @pre     The GPT unit must be running in continuous mode.
 *
 * @param[in] gptp      pointer to a @p GPTDriver object
 * @return              The current interval.
 * @notapi
 */
#define gpt_lld_get_interval(gptp) \
    ((gptcnt_t)(gptp)->BFTM->CMP / (ES32_CK_AHB_FREQUENCY / (gptp)->config->frequency))

/**
 * @brief   Returns the counter value of GPT peripheral.
 * @pre     The GPT unit must be running in continuous mode.
 * @note    The nature of the counter is not defined, it may count upward
 *          or downward, it could be continuously running or not.
 *
 * @param[in] gptp      pointer to a @p GPTDriver object
 * @return              The current counter value.
 * @notapi
 */
#define gpt_lld_get_counter(gptp) \
    ((gptcnt_t)((gptp)->BFTM->CNTR / (ES32_CK_AHB_FREQUENCY / (gptp)->config->frequency)))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (ES32_GPT_USE_BFTM0 == TRUE) && !defined(__DOXYGEN__)
    extern GPTDriver GPTD_BFTM0;
#endif
#if (ES32_GPT_USE_BFTM1 == TRUE) && !defined(__DOXYGEN__)
    extern GPTDriver GPTD_BFTM1;
#endif

#ifdef __cplusplus
extern "C" {
#endif
void gpt_lld_init(void);
void gpt_lld_start(GPTDriver *gptp);
void gpt_lld_stop(GPTDriver *gptp);
void gpt_lld_start_timer(GPTDriver *gptp, gptcnt_t interval);
void gpt_lld_stop_timer(GPTDriver *gptp);
void gpt_lld_polled_delay(GPTDriver *gptp, gptcnt_t interval);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_GPT == TRUE */

#endif /* HAL_GPT_LLD_H */

/** @} */
