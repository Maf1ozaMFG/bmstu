using Core.Interfaces;
using DatabaseModels;

namespace Core.Services;

public class GroupService
{
    private readonly IDataRepository<Group> _groupRepository;

    public GroupService(IDataRepository<Group> groupRepository)
    {
        _groupRepository = groupRepository;
    }

    public void CreateGroup(string name)
    {
        Group group = new Group();
        group.Name = name;
        group.CreationDate = DateTime.Now;
        group.CreationDate = DateTime.SpecifyKind(group.CreationDate, DateTimeKind.Utc);

        _groupRepository.Add(group);
    }

    public void UpdateGroupNameById(int id, string name)
    {
        try
        {
            var group = _groupRepository.GetById(id);
            if (group != null)
            {
                group.Name = name;
                _groupRepository.Update(group);
            }
            else
            {
                throw new Exception("Cannot find group by this ID");
            }
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public void UpdateCreationDateById(int id, DateTime newCreationDate)
    {
        var group = _groupRepository.GetById(id);
        if (group != null)
        {
            try
            {
                group.CreationDate = newCreationDate;
                _groupRepository.Update(group);
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
        }
        else
        {
            throw new Exception("Cannot find group by this ID");
        }
    }

    public Group GetById(int id)
    {
        try
        {
            var group = _groupRepository.GetById(id);

            return group == null ? throw new Exception("Cannot find group by this ID") : group;
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public IEnumerable<Group> GetAllGroups()
    {
        try
        {
            var groups = _groupRepository.GetAll();
            return groups;
        } catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public void DeleteGroupById(int id)
    {
        try
        {
            var group = _groupRepository.GetById(id);
            if (group == null)
                throw new Exception("Cannot find group by this ID");

            _groupRepository.Delete(group);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }
}

