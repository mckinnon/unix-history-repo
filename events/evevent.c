/******************************************************************************
 *
 * Module Name: evevent - Fixed Event handling and dispatch
 *              $Revision: 1.125 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2007, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government.  In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#include "acpi.h"
#include "acevents.h"

#define _COMPONENT          ACPI_EVENTS
        ACPI_MODULE_NAME    ("evevent")

/* Local prototypes */

static ACPI_STATUS
AcpiEvFixedEventInitialize (
    void);

static UINT32
AcpiEvFixedEventDispatch (
    UINT32                  Event);


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvInitializeEvents
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize global data structures for ACPI events (Fixed, GPE)
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEvInitializeEvents (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvInitializeEvents);


    /*
     * Initialize the Fixed and General Purpose Events. This is done prior to
     * enabling SCIs to prevent interrupts from occurring before the handlers are
     * installed.
     */
    Status = AcpiEvFixedEventInitialize ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to initialize fixed events"));
        return_ACPI_STATUS (Status);
    }

    Status = AcpiEvGpeInitialize ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to initialize general purpose events"));
        return_ACPI_STATUS (Status);
    }

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvInstallFadtGpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Completes initialization of the FADT-defined GPE blocks
 *              (0 and 1). This causes the _PRW methods to be run, so the HW
 *              must be fully initialized at this point, including global lock
 *              support.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEvInstallFadtGpes (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvInstallFadtGpes);


    /* Namespace must be locked */

    Status = AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    /* FADT GPE Block 0 */

    (void) AcpiEvInitializeGpeBlock (
                AcpiGbl_FadtGpeDevice, AcpiGbl_GpeFadtBlocks[0]);

    /* FADT GPE Block 1 */

    (void) AcpiEvInitializeGpeBlock (
                AcpiGbl_FadtGpeDevice, AcpiGbl_GpeFadtBlocks[1]);

    (void) AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE);
    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvInstallXruptHandlers
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install interrupt handlers for the SCI and Global Lock
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEvInstallXruptHandlers (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvInstallXruptHandlers);


    /* Install the SCI handler */

    Status = AcpiEvInstallSciHandler ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to install System Control Interrupt handler"));
        return_ACPI_STATUS (Status);
    }

    /* Install the handler for the Global Lock */

    Status = AcpiEvInitGlobalLockHandler ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to initialize Global Lock handler"));
        return_ACPI_STATUS (Status);
    }

    AcpiGbl_EventsInitialized = TRUE;
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvFixedEventInitialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install the fixed event handlers and enable the fixed events.
 *
 ******************************************************************************/

static ACPI_STATUS
AcpiEvFixedEventInitialize (
    void)
{
    ACPI_NATIVE_UINT        i;
    ACPI_STATUS             Status;


    /*
     * Initialize the structure that keeps track of fixed event handlers
     * and enable the fixed events.
     */
    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        AcpiGbl_FixedEventHandlers[i].Handler = NULL;
        AcpiGbl_FixedEventHandlers[i].Context = NULL;

        /* Enable the fixed event */

        if (AcpiGbl_FixedEventInfo[i].EnableRegisterId != 0xFF)
        {
            Status = AcpiSetRegister (
                        AcpiGbl_FixedEventInfo[i].EnableRegisterId, 0);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }
    }

    return (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvFixedEventDetect
 *
 * PARAMETERS:  None
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Checks the PM status register for active fixed events
 *
 ******************************************************************************/

UINT32
AcpiEvFixedEventDetect (
    void)
{
    UINT32                  IntStatus = ACPI_INTERRUPT_NOT_HANDLED;
    UINT32                  FixedStatus;
    UINT32                  FixedEnable;
    ACPI_NATIVE_UINT        i;


    ACPI_FUNCTION_NAME (EvFixedEventDetect);


    /*
     * Read the fixed feature status and enable registers, as all the cases
     * depend on their values.  Ignore errors here.
     */
    (void) AcpiHwRegisterRead (ACPI_MTX_DO_NOT_LOCK, ACPI_REGISTER_PM1_STATUS,
                &FixedStatus);
    (void) AcpiHwRegisterRead (ACPI_MTX_DO_NOT_LOCK, ACPI_REGISTER_PM1_ENABLE,
                &FixedEnable);

    ACPI_DEBUG_PRINT ((ACPI_DB_INTERRUPTS,
        "Fixed Event Block: Enable %08X Status %08X\n",
        FixedEnable, FixedStatus));

    /*
     * Check for all possible Fixed Events and dispatch those that are active
     */
    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        /* Both the status and enable bits must be on for this event */

        if ((FixedStatus & AcpiGbl_FixedEventInfo[i].StatusBitMask) &&
            (FixedEnable & AcpiGbl_FixedEventInfo[i].EnableBitMask))
        {
            /* Found an active (signalled) event */

            IntStatus |= AcpiEvFixedEventDispatch ((UINT32) i);
        }
    }

    return (IntStatus);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvFixedEventDispatch
 *
 * PARAMETERS:  Event               - Event type
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Clears the status bit for the requested event, calls the
 *              handler that previously registered for the event.
 *
 ******************************************************************************/

static UINT32
AcpiEvFixedEventDispatch (
    UINT32                  Event)
{


    ACPI_FUNCTION_ENTRY ();


    /* Clear the status bit */

    (void) AcpiSetRegister (AcpiGbl_FixedEventInfo[Event].StatusRegisterId, 1);

    /*
     * Make sure we've got a handler.  If not, report an error.
     * The event is disabled to prevent further interrupts.
     */
    if (NULL == AcpiGbl_FixedEventHandlers[Event].Handler)
    {
        (void) AcpiSetRegister (AcpiGbl_FixedEventInfo[Event].EnableRegisterId, 0);

        ACPI_ERROR ((AE_INFO,
            "No installed handler for fixed event [%08X]",
            Event));

        return (ACPI_INTERRUPT_NOT_HANDLED);
    }

    /* Invoke the Fixed Event handler */

    return ((AcpiGbl_FixedEventHandlers[Event].Handler)(
                                AcpiGbl_FixedEventHandlers[Event].Context));
}


