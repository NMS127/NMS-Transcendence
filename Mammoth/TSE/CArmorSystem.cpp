//	CArmorSystem.cpp
//
//	CArmorSystem class
//	Copyright (c) 2016 by Kronosaur Productions, LLC. All Rights Reserved.

#include "PreComp.h"

CArmorSystem CArmorSystem::m_Null;

void CArmorSystem::AccumulatePerformance (SShipPerformanceCtx &Ctx) const

//	AccumulatePerformance
//
//	Accumulates performance metrics.

	{
	for (const CInstalledArmor &Armor : *this)
		{
        CItemCtx ItemCtx(Ctx.pShip, &Armor);
        ItemCtx.GetArmor()->AccumulatePerformance(ItemCtx, Ctx);
		}
	}

void CArmorSystem::AccumulatePowerUsed (SUpdateCtx &Ctx, CSpaceObject *pObj, int &iPowerUsed, int &iPowerGenerated)

//	AccumulatePowerUsed
//
//	Compute power used/generated by armor this tick.

	{
	for (const CInstalledArmor &Armor : *this)
		{
        CItemCtx ItemCtx(pObj, &Armor);
        ItemCtx.GetArmorClass()->AccumulatePowerUsed(ItemCtx, Ctx, iPowerUsed, iPowerGenerated);
		}
	}

int CArmorSystem::CalcTotalHitPoints (int *retiMaxHP) const

//	CalcTotalHitPoints
//
//	Computes total hit points (and max hit points) for all armor segments.

	{
	int iTotalHP = 0;
	int iTotalMaxHP = 0;

	for (const CArmorItem ArmorItem : *this)
		{
		int iMaxHP;
		int iHP = ArmorItem.GetHP(&iMaxHP);
		iTotalHP += iHP;
		iTotalMaxHP += iMaxHP;
		}

	if (retiMaxHP)
		*retiMaxHP = iTotalMaxHP;

	return iTotalHP;
	}

int CArmorSystem::GetMaxLevel () const

//	GetMaxLevel
//
//	Returns the maximum level of armor.

	{
	int iMaxLevel = -1;

	for (const CArmorItem ArmorItem : *this)
		{
		if (ArmorItem.GetLevel() > iMaxLevel)
			iMaxLevel = ArmorItem.GetLevel();
		}

	return iMaxLevel;
	}

void CArmorSystem::Install (CSpaceObject &Source, const CShipArmorDesc &Desc, bool bInCreate)

//  Install
//
//  Install armor segments

    {
	DEBUG_TRY

    ASSERT(m_Segments.GetCount() == 0);

    //  We insert armor segments too

    CItemListManipulator Items(Source.GetItemList());

    //  Loop over all sections

	m_Segments.InsertEmpty(Desc.GetCount());
	for (int i = 0; i < Desc.GetCount(); i++)
		{
        const CShipArmorSegmentDesc &Sect = Desc.GetSegment(i);

		//	Create an armor segment item

        CItem ArmorItem;
        Sect.CreateArmorItem(&ArmorItem);
		if (!ArmorItem.IsArmor())
			throw CException(ERR_FAIL);

        //  Add the item. We leave the cursor on the newly created item.

		Items.AddItem(ArmorItem);

		//	Install

		m_Segments[i].Install(Source, Items, i, bInCreate);
		}

    //  Initialize other properties

    m_iHealerLeft = 0;

	DEBUG_CATCH
    }

bool CArmorSystem::IsImmune (SpecialDamageTypes iSpecialDamage) const

//	IsImmune
//
//	Returns TRUE if all armor segments are immune to the given special damage.

	{
	for (CArmorItem ArmorItem : *this)
		{
		if (!ArmorItem.IsImmune(iSpecialDamage))
			return false;
		}

	return (m_Segments.GetCount() > 0);
	}

void CArmorSystem::ReadFromStream (SLoadCtx &Ctx, CSpaceObject &Source)

//  ReadFromStream
//
//  Read from stream

    {
	DWORD dwCount;
	Ctx.pStream->Read(dwCount);
	m_Segments.InsertEmpty(dwCount);
	for (int i = 0; i < (int)dwCount; i++)
		m_Segments[i].ReadFromStream(Source, i, Ctx);

    //  Read other properties

    if (Ctx.dwVersion >= 128)
        Ctx.pStream->Read(m_iHealerLeft);
    else
        m_iHealerLeft = 0;
    }

bool CArmorSystem::RepairAll (CSpaceObject *pSource)

//	RepairAll
//
//	Makes sure all armor segments are at full hit points. Returns TRUE if we
//	repaired anything.

	{
	bool bRepaired = false;
	for (CInstalledArmor &Armor : *this)
		{
		int iHP = Armor.GetHitPoints();
		int iMaxHP = Armor.GetMaxHP(pSource);

		if (iHP < iMaxHP)
			{
			Armor.SetHitPoints(iMaxHP);
			bRepaired = true;
			}
		}

	return true;
	}

bool CArmorSystem::RepairSegment (CSpaceObject *pSource, int iSeg, int iHPToRepair, int *retiHPRepaired)

//	RepairSegment
//
//	Repairs the given number of hit points on the segment. Returns TRUE if we
//	repaired anything.
//
//	NOTE: If iHPToRepair is negative, we repair all hit points.

	{
	if (iSeg < 0 || iSeg >= m_Segments.GetCount())
		{
		if (retiHPRepaired) *retiHPRepaired = 0;
		return false;
		}

	CInstalledArmor &Armor = GetSegment(iSeg);
	int iHP = Armor.GetHitPoints();
	int iMaxHP = Armor.GetMaxHP(pSource);

	//	Compute the new HP for the segment. If iHPToRepair is negative, then we
	//	repair all damage.

	int iNewHP;
	if (iHPToRepair < 0)
		iNewHP = iMaxHP;
	else
		iNewHP = Min(iHP + iHPToRepair, iMaxHP);

	//	Return how many HP we repaired

	if (retiHPRepaired)
		*retiHPRepaired = iNewHP - iHP;

	//	If nothing to do, nothing to do.

	if (iNewHP == iHP)
		return false;

	Armor.SetHitPoints(iNewHP);
	return true;
	}

void CArmorSystem::SetSegmentHP (CSpaceObject &SourceObj, int iSeg, int iHP)

//	SetSegmentHP
//
//	Sets the segment to the given hit points.

	{
	if (iSeg < 0 || iSeg >= m_Segments.GetCount())
		throw CException(ERR_FAIL);

	CInstalledArmor &Armor = GetSegment(iSeg);
	int iMaxHP = Armor.GetMaxHP(&SourceObj);
	int iNewHP = Max(0, Min(iHP, iMaxHP));

	Armor.SetHitPoints(iNewHP);
	}

void CArmorSystem::SetTotalHitPoints (CSpaceObject *pSource, int iNewHP)

//	SetTotalHitPoints
//
//	Sets the hit points for the total system, distributing as appropriate.

	{
	//	First figure out some totals

	int iTotalMaxHP = 0;
	int iTotalHP = CalcTotalHitPoints(&iTotalMaxHP);

	//	Compute the delta

	iNewHP = Max(0, Min(iNewHP, iTotalMaxHP));
	int iDeltaHP = iNewHP - iTotalHP;
	if (iDeltaHP == 0)
		return;

	//	Slightly different algorithms for healing vs. destroying.

	if (iDeltaHP > 0)
		{
		int iHPLeft = iDeltaHP;
		int iTotalHPNeeded = iTotalMaxHP - iTotalHP;

		for (CInstalledArmor &Armor : *this)
			{
			int iHP = Armor.GetHitPoints();
			int iMaxHP = Armor.GetMaxHP(pSource);

			//	To each according to their need
			//
			//	NOTE: iTotalHPNeeded cannot be 0 because that would imply that iTotalHP
			//	equals iTotalMaxHP. But if that were the case, iDeletaHP would be 0, so
			//	we wouldn't be in this code path.

			int iHPNeeded = iMaxHP - iHP;
			int iHPToHeal = Min(iHPLeft, iDeltaHP * iHPNeeded / iTotalHPNeeded);

			//	Heal

			Armor.SetHitPoints(iHP + iHPToHeal);

			//	Keep track of how much we've used up.

			iHPLeft -= iHPToHeal;
			}

		//	If we've got extra hit points, then distribute around.

		for (CInstalledArmor &Armor : *this)
			{
			if (iHPLeft > 0)
				{
				int iHP = Armor.GetHitPoints();
				int iMaxHP = Armor.GetMaxHP(pSource);

				if (iHP < iMaxHP)
					{
					Armor.SetHitPoints(iHP + 1);
					iHPLeft--;
					}
				}
			else
				break;
			}
		}
	else
		{
		int iDamageLeft = -iDeltaHP;
		
		for (CInstalledArmor &Armor : *this)
			{
			int iHP = Armor.GetHitPoints();
			int iMaxHP = Armor.GetMaxHP(pSource);

			//	Damage in proportion to HP left.
			//
			//	NOTE: iTotalHP cannot be 0 because that would imply that iDeltaHP is
			//	non-negative, in which case we would not be on this code path.

			int iHPToDamage = Min(iDamageLeft, -iDeltaHP * iHP / iTotalHP);

			//	Damage

			Armor.SetHitPoints(iHP - iHPToDamage);

			//	Keep track of how much damage we've used up

			iDamageLeft -= iHPToDamage;
			}

		//	If we've got extra damage, then distribute

		for (CInstalledArmor &Armor : *this)
			{
			if (iDamageLeft > 0)
				{
				int iHP = Armor.GetHitPoints();

				if (iHP > 0)
					{
					Armor.SetHitPoints(iHP - 1);
					iDamageLeft--;
					}
				}
			else
				break;
			}
		}
	}

bool CArmorSystem::Update (SUpdateCtx &Ctx, CSpaceObject *pSource, int iTick)

//	Update
//
//	Must be called once per tick to update the armor system. We return TRUE if 
//	the update modified the properties of the armor (e.g., hit points).

	{
	//	We only update armor once every 10 ticks.

    if ((iTick % CArmorClass::TICKS_PER_UPDATE) != 0)
		return false;

	//	Update all segments.

	bool bSystemModified = false;
    for (CInstalledArmor &Armor : *this)
        {
		CItemCtx ItemCtx(pSource, &Armor);
		bool bArmorModified;

        Armor.GetClass()->Update(ItemCtx, Ctx, iTick, &bArmorModified);
        if (bArmorModified)
            bSystemModified = true;
        }

	//	Done

	return bSystemModified;
	}

void CArmorSystem::WriteToStream (IWriteStream *pStream) const

//  WriteToStream
//
//  Write

    {
    DWORD dwSave = m_Segments.GetCount();
	pStream->Write(dwSave);

	for (const CInstalledArmor &Armor : *this)
		Armor.WriteToStream(pStream);

    //  Write other properties

	pStream->Write(m_iHealerLeft);
    }
